
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('month', type= str)
parser.add_argument('year', type= str)
month_year = parser.parse_args()
month = month_year.month
year = month_year.year

assert isinstance(int(month), int)
assert (int(month) > 0 and int(month)<=12), "Illigal value"
assert isinstance(int(year), int)
assert int(year) > 0, "Illigal value"

outcome_data = pd.read_excel(fr"C:\Users\anton\OneDrive\Desktop\инфа\outcome_{month}.{year}.xlsx")
outcome_data
outcome_data["День"] = [int(x.split()[0]) for x in outcome_data["Дата"]]
outcome_data

fig, ax = plt.subplots(constrained_layout=True)
sns.barplot(
  data=outcome_data,
  x="Сумма",
  y="Категория",
  orient = "h",
  estimator="sum",
  errorbar=None,
  ax=ax
)
plt.title(f'{month}.{year}')
plt.show()
