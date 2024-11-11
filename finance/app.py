import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Obtain user's stocks and shares
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])
    # Obtain user's cash balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    # Initialize grand total
    grand_total = cash

    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["total_value"] = stock["price"] * stock["total_shares"]
        grand_total += stock["total_value"]

    return render_template("index.html", stocks=stocks, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        # Ensure username was submitted
        if not symbol:
            return apology("must enter a valid stock quote symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must enter a positive integer for number of shares", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("symbol not found")

        price = quote["price"]
        total = price * int(shares)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if cash < total:
            return apology("insufficient funds in account")

        # Update users table in finance.db
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, session["user_id"])
        # Add purchase to transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, shares, price, "buy")
        if shares == "1":
            flash(f"You have just purchased {shares} share of {symbol} with {usd(total)}!")
        else:
            flash(f"You have just purchased {shares} shares of {symbol} with {usd(total)}!")
        return redirect('/')
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Select info on user's transactions, orderd by most recent first
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY id DESC", session["user_id"])
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
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


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
    if request.method == "POST":
        # Ensure quote search was submitted
        if not request.form.get("symbol"):
            return apology("must enter a valid stock quote symbol", 400)

        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote is None:
            return apology("symbol not found", 400)
        else:
            # Show user the price
            return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must create username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must create password", 400)
        # Ensure password confirmation was submitted
        elif not request.form.get("password"):
            return apology("must confirm password", 400)
        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must provide matching passwords", 400)
        # Create variables for username and hashed password
        username = request.form.get("username")
        hashedpass = generate_password_hash(request.form.get("password"))
        # Ensure username does not already exist
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 0:
            return apology("this username already exists, please choose another", 400)
        # Insert username and hashed password into finance.db
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashedpass)
        # Query database for username of newly registered user
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        # Remember which user is logged in
        session["user_id"] = rows[0]["id"]
        # Return to homepage
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Obtain user's stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])
    if request.method == "POST":
        # Obtain user's inserted symbol, and shares
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Deal with possible issues
        if symbol is None:
            return apology("must select a valid stock quote symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must enter a  positive integer for number of shares")
        else:
            symbol = symbol.upper()
            shares = int(shares)

        for stock in stocks:
            # Deal with possibility of not enough shares
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("insufficient amount of shares in possession to sell")
                else:
                    quote = lookup(symbol)
                    price = quote["price"]
                    total_sale = shares * price
                    # Update users cash in users table
                    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                               total_sale, session["user_id"])
                    # Add purchase to transactions table
                    db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
                               session["user_id"], symbol, (-shares), price, "sell")
                    if shares == 1:
                        flash(
                            f"You have just sold {shares} share of {symbol} for {usd(total_sale)}!")
                    else:
                        flash(
                            f"You have just sold {shares} shares of {symbol} for {usd(total_sale)}!")
        # Return to homepage
        return redirect("/")
    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/delete", methods=["POST"])
def delete_history():
    # Forget transaction
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM transactions WHERE id = ?", id)
    return redirect("/history")
