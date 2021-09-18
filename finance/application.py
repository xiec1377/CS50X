import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date 

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM portfolio WHERE id = :user_id", user_id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
    total = 0
    for stock in stocks:
        name = lookup(stock["symbol"])["name"]
        price = lookup(stock["symbol"])["price"]
        total_price = price * stock["shares"]
        total += total_price
    return render_template("index.html", stocks=stocks, cash=round(cash, 2), total=round(total, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User gets to route through "GET"
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Get variables from user input
        symbol = lookup(request.form.get("symbol"))["symbol"]
        shares = int(request.form.get("shares"))

        # Displays apology for invalid user inputs
        if not request.form.get("symbol"):
            return apology("Please provide valid symbol.")
        elif not request.form.get("shares") or shares <= 0:
            return apology("Please provide valid number of shares.")
        elif not symbol:
            return apology("Please provide valid stock.")

        # Obtain cash balance of user given their id
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]["cash"]
        # Obtain total price of shares user wishes to purchase
        total_price = shares * lookup(request.form.get("symbol"))["price"]
        # Displays apology if user does not have enough cash
        if cash < total_price:
            return apology("You do not have enough cash.")
        else:
            updated_cash = cash - total_price
            stock = db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol=:symbol",
                               id=session["user_id"], symbol=symbol)
            if not stock:
                db.execute("INSERT INTO portfolio(id, symbol, shares) VALUES (:id, :symbol, :shares)",
                           id=session["user_id"], symbol=symbol, shares=shares)
            else:
                shares += stock[0]["shares"]
                db.execute("UPDATE portfolio SET shares = :shares WHERE id = :id AND symbol = :symbol",
                           shares=shares, id=session["user_id"], symbol=symbol)
            # Calculate and update cash after transaction
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=updated_cash, id=session["user_id"])
            db.execute("INSERT INTO transactions (id, symbol, name, shares, price, date) VALUES(:id, :symbol, :name, :shares, :price, :date)",
                       id=session["user_id"],
                       symbol=request.form.get("symbol"),
                       name=lookup(request.form.get("symbol"))["name"],
                       shares=shares,
                       price=total_price,
                       date=date.today())
        flash("Bought!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query data with the transactions history
    transactions = db.execute("SELECT symbol, name, shares, price, date FROM transactions WHERE id = :id ORDER BY date DESC", id=session["user_id"])

    # redirect user to index page
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Change password"""
    # User reached route via GET
    if request.method == "GET":
        return render_template("change_password.html")
    # User reached route via POST
    else:
        # Get user inputs
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        username = request.form.get("username")

        # Ensure fields are filled
        if not username:
            return apology("Username not provided.")
        elif not password:
            return apology("Password not provided.")
        elif not confirmation:
            return apology("Please confirm your password.")
        # Ensure password matches confirmation
        elif password != confirmation:
            return apology("Passwords do not match")
        else:
            # Updates hash column in users table with new hashed password
            db.execute("UPDATE users SET hash = :hash WHERE username = :username", hash=generate_password_hash(request.form.get("change")), username=username)
            rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
            session["user_id"] = rows[0]["id"]
            return redirect ("/")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via GET
    if request.method == "GET":
        return render_template("quote.html")
    # User reached route via POST
    else:
        search_quote = lookup(request.form.get("symbol"))
        if not search_quote:
            return apology("Please provide valid stock.")
        else:
            return render_template("quoted.html", search_quote=search_quote)



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via GET
    if request.method == "GET":
        return render_template("register.html")
    # User reached route via POST
    else:
        # Ensures fields are filled
        if not request.form.get("username"):
            return apology("Username not provided")
        elif not request.form.get("password"):
            return apology("Password not provided")
        elif not request.form.get("confirmation"):
            return apology("Please confirm your password")
        # Ensures password matches confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match")
        # Checks if username is taken
        elif db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("Username taken")
        # Inserts data into users table
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via GET
    if request.method == "GET":
    # query database with the transactions history
        symbol = db.execute("SELECT symbol FROM portfolio WHERE id=:id",
                            id = session["user_id"])
        return render_template("sell.html", symbol=symbol)
    # User reached route via POST
    else:
        # Get user inputs
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")
        price = lookup(symbol)["price"]
        total_price = price * shares
        num_current = db.execute("SELECT shares FROM portfolio WHERE id = :id AND symbol = :symbol",
                                 id=session["user_id"], symbol=symbol)[0]["shares"]
        num_after = num_current - shares
        # Checks if user has enough shares to sell
        if num_after < 0:
            return apology("You do not own enough shares.")
        # Deletes stock data from portfolio if no shares left after transaction
        elif num_after == 0:
            # Delete stock from portfolio
            db.execute("DELETE FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        # Updates portfolio data with new number of shares
        else:
            db.execute("UPDATE portfolio SET shares = :shares WHERE id = :id AND symbol = :symbol",
                           shares=num_after, id=session["user_id"], symbol=symbol)
        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                              id=session["user_id"])[0]["cash"]
        updated_cash = cash + total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id",
                       cash=updated_cash, id=session["user_id"])
        db.execute("INSERT INTO transactions (id, symbol, name, shares, price, date) VALUES (:id, :symbol, :name, :shares, :price, :date)",
                       id=session["user_id"],
                       symbol=symbol,
                       name=lookup(request.form.get("symbol"))["name"],
                       shares=-shares,
                       price=-total_price,
                       date=date.today())
        flash("Sold!")
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
