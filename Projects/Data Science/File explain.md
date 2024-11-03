**Hypothesis statement:**
- Does GPA affect no. of SAT test taken
   
**Step 1:**
- We drop csv file "Simple linear regression.csv" into same directory folder path as main .ipynb file is. 

**Step 2:**
- We imported matplotlib/seaborn, numpy, pandas and statsmodels

- Load the data through `pd.read_csv('Simple linear regression.csv')`

- Create graph with y-axis (GPA) and x-axis (SAT), and plot scattor graph

- Show resutls therough `results.summary()`

- From 'results.summary()', Find the 2 "coef" data from const 0.2750 = b0, and SAT 0.0017 = b1 
- Add in code of 'yhat = 0.0017*x1 + 0.275'
- Recreate the graph with new line 'fig = plt.plot(x1,yhat, lw=4, c='orange', label ='regression line')' to show line.

**Step 3:**
- From the graph, look at where the line correlation is at.
- Since it's showing a positive correlation, we can say...
- In conclusion, the higher the SAT count, the higher the GPA results.
