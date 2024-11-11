import os

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    # Obtain number of people user wishes to have grouped

    return render_template("index.html")

@app.route("/input")
def input():
    # Have a 2 column table for user to fill names into and select preferences with

    return render_template("input.html")

@app.route("/groupings")
def groupings():
    # Display groupings in table

    return render_template("groupings.html")
