#!/bin/bash

# This script just updates all the quote banks to be up to date.
# The quotes will be updated for each commit, but you can also just run this
# if there's like. a specific quote you want. idfk

curl -o monkeytype-quotes/english.json https://raw.githubusercontent.com/monkeytypegame/monkeytype/master/frontend/static/quotes/english.json
# could expand this to other languages when needed

