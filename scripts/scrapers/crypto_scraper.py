#!/anaconda3/bin/python

import time
import urllib.request
import json
import mysql.connector
from datetime import datetime

ENV_KEY='CRYPTO_COMPARE_API_KEY'
HOST_KEY='SQL_HOST'
USER_KEY='SQL_USER'
PASS_KEY='SQL_PASS'

def checkOrExit(key, env_vars):
  if key not in env_vars:
    print('key '+key+' not found, exiting')
    exit(1)

def insert(table, timestamp, humanDate, value, cursor):
  sql = "INSERT INTO "+table+" (timestamp, time, value ) VALUES (%s, %s, %s)"
  val = ( timestamp, humanDate, value)
  cursor.execute(sql, val)

def getData():
  # get timestamp
  timestamp = int(time.time())

  now = datetime.now()
  humanDate = now.strftime("%Y/%m/%d %H:%M")

  # get env_vars
  env_vars = {}
  with open(".env") as f:
    for line in f:
      key, value = line.strip().split('=', 1)
      env_vars[key] = value

  # check keys
  checkOrExit(ENV_KEY, env_vars)
  checkOrExit(HOST_KEY, env_vars)
  checkOrExit(USER_KEY, env_vars)
  checkOrExit(PASS_KEY, env_vars)

  # get data
  url="https://min-api.cryptocompare.com/data/pricemulti?api_key=" +env_vars[ENV_KEY] +"&fsyms=BTC,ETH,XRP,LTC,BCH,EOS,TRX&tsyms=EUR"
  print(url)
  req = urllib.request.Request(url=url)
  with urllib.request.urlopen(req) as f:
    response = f.read().decode('utf-8')
    print( response )

  # parse
  result_json = json.loads(response)
  btc = result_json["BTC"]["EUR"]
  eth = result_json["ETH"]["EUR"]
  xrp = result_json["XRP"]["EUR"]
  ltc = result_json["LTC"]["EUR"]
  bch = result_json["BCH"]["EUR"]
  eos = result_json["EOS"]["EUR"]
  trx = result_json["TRX"]["EUR"]

  #python -m pip install mysql-connector
  # insert sql
  mydb = mysql.connector.connect(host=env_vars[HOST_KEY], user=env_vars[USER_KEY], passwd=env_vars[PASS_KEY], database='trading' )
  mycursor = mydb.cursor()

  insert('live_btc', timestamp, humanDate, btc, mycursor)
  insert('live_eth', timestamp, humanDate, eth, mycursor)
  insert('live_xrp', timestamp, humanDate, xrp, mycursor)
  insert('live_ltc', timestamp, humanDate, ltc, mycursor)
  insert('live_bch', timestamp, humanDate, bch, mycursor)
  insert('live_eos', timestamp, humanDate, eos, mycursor)
  insert('live_trx', timestamp, humanDate, trx, mycursor)

  mydb.commit()

getData()

