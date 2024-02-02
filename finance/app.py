import os

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, check_password

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    data = db.execute("SELECT * FROM stocks WHERE user_id=?", session["user_id"])
    balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    balance = balance[0]["cash"]

    total = balance
    for stock in data:
        total += float(stock["total"])

        stock["price"] = float(stock["price"])
        stock["total"] = float(stock["total"])

    return render_template("index.html", data=data, balance=balance, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol", 400)

        if not request.form.get("shares"):
            return apology("must provide a number of shares", 400)

        symbol = request.form.get("symbol")
        number = request.form.get("shares")
        quote = lookup(symbol)

        if not number.isdigit():
            return apology("share must be a number", 400)

        if '.' in number:
            return apology("share must be an integer", 400)

        number = int(number)
        if number < 0:
            return apology("share must be greater than 0", 400)

        if quote == None:
            return apology("Stock's symbol does not exist", 400)

        price = quote["price"]
        value = number * price
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        cash = cash[0]["cash"]

        user = session["user_id"]

        exist = db.execute("SELECT * FROM stocks WHERE user_id=? AND symbol=?", user, symbol)
        if not exist:
            db.execute("INSERT INTO stocks (user_id, symbol, comp_name) VALUES(?,?,?)",user, symbol, quote["name"])

        total = cash - value
        if total < 0:
            return apology("insufficient cash", 403)

        current = db.execute("SELECT shares FROM stocks WHERE user_id=? AND symbol=?", user, symbol)
        current = current[0]["shares"]

        if current:
            new = current + number
        else:
            new = number

        db.execute("UPDATE stocks SET shares=?, price=?, total=? WHERE user_id=? AND symbol=?",
                       new, price, new * price, user, symbol)

        db.execute("INSERT INTO history (user_id, symbol, comp_name, shares, price, method, total, date_time) VALUES(?,?,?,?,?,?,?,?)",  user, symbol, quote["name"], number, usd(price), "Buy", usd(number * price), datetime.now())

        db.execute("UPDATE users SET cash=? WHERE id=?", total, user)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT * FROM history WHERE user_id=?", session["user_id"])
    return render_template("history.html", data=data)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("Stock's symbol does not exist", 400)
        else:
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        users = db.execute("SELECT * FROM users")
        user = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        for name in users:
            if name["username"] == user:
                return apology("username aleady exists", 400)

        if not check_password(password):
            return apology("password must have more than 8 characters, uppercase, lowercase and digit", 400)

        if password != confirmation:
            return apology("the password and the confirmation do not match", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", user, generate_password_hash(password))

        return render_template("registered.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = session["user_id"]
    data = db.execute("SELECT * FROM stocks WHERE user_id=?", user)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol == None:
            return apology("you must choose a stock", 403)

        found = 1
        for stock in data:
            if symbol == stock["symbol"]:
                found = 0
                break
        if found:
            return apology("you do not own ant share of that stock", 403)

        quote = lookup(symbol)
        price = quote["price"]

        shares = db.execute("SELECT shares FROM stocks WHERE user_id=? AND symbol=?", user, symbol)
        shares = shares[0]['shares']
        number = request.form.get("shares")

        if number == None:
            return apology("share must be a number", 400)
        number = int(number)
        if number < 1 or number > shares:
            return apology("invalid number of shares", 400)

        new = shares - number
        cash = db.execute("SELECT cash FROM users WHERE id=?", user)
        cash = cash[0]['cash']
        balance = cash + (number * price)

        db.execute("UPDATE stocks SET shares=?, price=?, total=? WHERE user_id=? AND symbol=?",
                       new, price, new * price, user, symbol)

        db.execute("INSERT INTO history (user_id, symbol, comp_name, shares, price, method, total, date_time) VALUES(?,?,?,?,?,?,?,?)",  user, symbol, quote["name"], number, usd(price), "Sell", usd(number * price), datetime.now())

        db.execute("UPDATE users SET cash=? WHERE id=?", balance, user)

        return redirect("/")
    else:
        return render_template("sell.html", data=data)
