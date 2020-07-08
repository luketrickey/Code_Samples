import operator
import os

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import PolynomialFeatures
from sklearn.datasets import load_boston

%matplotlib inline

boston_dataset = load_boston()

print(boston_dataset.keys())
boston_dataset.DESCR

boston = pd.DataFrame(boston_dataset.data, 
                      columns=boston_dataset.feature_names)
boston.head()

boston['MEDV'] = boston_dataset.target

x = boston['LSTAT']
y = boston['MEDV']

x = x[:, np.newaxis]
y = y[:, np.newaxis]

model = LinearRegression()
model.fit(x, y)
y_pred = model.predict(x)

plt.scatter(x, y, s=10)
plt.plot(x, y_pred, color='r')
plt.show()

polynomial_features = PolynomialFeatures(degree=15)
x_poly = polynomial_features.fit_transform(x)

model.fit(x_poly, y)
y_poly_pred = model.predict(x_poly)

rmse = np.sqrt(mean_squared_error(y,y_poly_pred))
r2 = r2_score(y,y_poly_pred)
print(rmse)
print(r2)

plt.scatter(x, y, s=10)
sort_axis = operator.itemgetter(0)
sorted_zip = sorted(zip(x,y_poly_pred), key=sort_axis)
x, y_poly_pred = zip(*sorted_zip)
plt.plot(x, y_poly_pred, color='g')
plt.show()