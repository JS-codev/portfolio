


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Video Demo</title>
</head>
<body>
    <h1>Demo Video</h1>
    <video controls>
        <source src="https://github.com/user-attachments/assets/32b51621-ec40-4d6c-95ef-ec73d2001bae" type="video/mp4">
        Your browser does not support the video tag.
    </video>
</body>
</html>

---

**Explanation:**

**Step 1: Add header & requried image**
- Put logo image in path `src/assets/image.png`

- Create a `Header.jsx` for title (under `Src/components/Header.jsx`)
- `index.css` contains global styles that can be applied to define overall styling of an app. This styling for elements includes body, headings, link, container styles.
- For example, we can use the `#header` style with `text-align: center` to center the title and logo.
    - To enable styling for `#header`, add `id='header'` inside of opening `<header>` tag
```jsx
//Header.jsx
import logo from '../assets/investment-calculator-logo.png';
export default function Header() {
    return (
    <header id='header'> 
    {/* Above id applies text-align: center that will move title & logo to center*/}
        <img src={logo} alt='Logo showing money bag :D' />
        <h1>Investment Calculator</h1>
    </header>
}
```

- We then add `<Header />` file component into `App.jsx` for it to run
  - `App.jsx` is the top-level component in React. It defines the layout of an app and includes other components that make up the user interface (UI).

```jsx
//App.jsx
import Header from './components/Header.jsx';
function App() {
    return (    
        <Header />
        )
}
export default App
```
**Step 2: Adding and updating user input**
- Create `UserInput.jsx` that returns a section that takes in user-input in numerical for variables of `initialInvestment`, `annualInvestment`, `expectedReturn`, and `duration`. 
    - `initialInvestment` represents the amount of money initially invested/deposited at the start of the investment.
    - `annualInvestment` indicates the additional amount of money contributed to the investment yearly.
    - `expectedReturn` represents the expected annual rate of return on the investment (%).
    - `duration` represents the duration of the investment in years.
- Create a variable `handleInputChange` that allows the user to input values into the 4 input fields.

```jsx
//UserInput.jsx
import { useState } from 'react';
export default function UserInput({ onChange }) {
    // Local state to manage user inputs (if not managed by parent)
    const [userInput, setUserInput] = useState({
        initialInvestment: '10000',
        annualInvestment: '1200',
        expectedReturn: '7',
        duration: '12'
    });

    //Allows user to input values in the 4 variable fields (UI element input box)
    const handleInputChange = (field, value) => {
    // Handle user input change and call onChange if it's passed
    const updatedInput = { ...userInput, [field]: value };
    setUserInput(updatedInput);

    // If onChange callback is provided, pass updated input field to it
    if (onChange) {
        onChange(field, value);
    }
};

return (
        <section id='user-input'>
            <div className='input-group'>
                <p>
                    <label>Initial Investment (USD$)</label>
                    <input
                        type='number'
                        required
                        value={userInput.initialInvestment}
                        onChange={(event) => handleInputChange('initialInvestment', event.target.value)}
                    />
                </p>
            </div>
            //repeat paragraph for other 3 variables...
         </section>
    );
}
 ```
 - Now we can add `<UserInput />` to function App() in `App.jsx` for it to run
 
**Step 3: Calculates the inputed values**
- In order to pass the userInput values into `Results.jsx` component:
    - Move the `UserInput.jsx` component (`handleChange` and `userInput`) into the `App.jsx` component so that values can be passed into new created `Results.jsx` file
    - Move `import { useState } from 'react';` from `UserInput.jsx` to `App.jsx` also
    - In `App.jsx`, update `<UserInput />` to `<UserInput userInput={userInput} onChange={handleChange} />` so that values in userInput / handleChange gets passed as a value to `Userinput.jsx` component 

- Create an `investment.js` file that has these 4 variables for calculation:
```jsx
//investment.js
export function calculateInvestmentResults({
    initialInvestment,
    annualInvestment,
    expectedReturn,
    duration
}) {
    const annualData = [];
    let investmentValue = initialInvestment;

    for (let i = 0; i < duration; i++) {
        const interestEarnedInYear = investmentValue * (expectedReturn / 100);
        investmentValue += interestEarnedInYear + annualInvestment;
        annualData.push({ 
            year: i + 1, // year identifier
            interest: interestEarnedInYear, // the amount of interest earned in this year
            valueEndOfYear: investmentValue, // investment value at end of year
            annualInvestment: annualInvestment // investment added in this year
        });
    }
    return annualData;
}
```
- In addtion, create a formatter that rounds off numerical values to 2 decimal place.
```jsx
// Example Usage: formatter.format(1000) => yields "$1,000"
export const formatter = new Intl.NumberFormat("en-US", {
    style: "currency",
    currency: "USD",
    minimumFractionDigits: 2, //round off to 2 d.p
    maximumFractionDigits: 2
});
```
**Step 4: Display the caluclated results**
- Import the `calculateInvestmentResults` function and `formatter` from `investment.js` into `results.jsx `
- Then take in the user's inputed values from `calculateInvestmentResults` and put them into the `resultsData` variable.
```jsx
//results.jsx
import { calculateInvestmentResults, formatter } from '../util/investment.js';

export default function Results({ input }) { //takes in UserInput values from App.jsx
    const resultsData = calculateInvestmentResults(input); //place values into investment.js to calculates investment results
    const initialInvestment = resultsData[0].valueEndOfYear - resultsData[0].interest - resultsData[0].annualInvestment; //Calculates and find the first user's input for Initial Investment for later further calculation
```

- Create a table to display the results:
```jsx
 return (
        <table id='result'>
            <thead>
                <tr> 
                    <th>Year</th>
                    <th>Investment Value</th>
                    <th>Interest (Year)</th>
                    <th>Total Interest</th>
                    <th>Invested Capital</th>
                </tr>
            </thead>
            <tbody>
                {resultsData.map(yearData => {
                    const totalInterest = yearData.valueEndOfYear - yearData.annualInvestment * yearData.year - initialInvestment;
                    const totalAmountInvested = yearData.valueEndOfYear - totalInterest;

                    return (
                        <tr key={yearData.year}>
                            <td>{yearData.year}</td>
                            {/* Use formatter.format() to display the investment value to 2 decimal places */}
                            <td>{formatter.format(yearData.valueEndOfYear)}</td>
                            <td>{formatter.format(yearData.interest)}</td>
                            <td>{formatter.format(totalInterest)}</td>
                            <td>{formatter.format(totalAmountInvested)}</td> {/* Ensure only necessary columns */}
                        </tr>
                    );
                })}
            </tbody>
        </table>
    );
```
- The result table will produce following attributes: `Year`, `Investment Value`, `Interest (Year)`, `Total Interest`, and `Invested Capital`
    - `Year`: Displays the number of rows corresponding to the given duration value.
    - `Investment Value`: Represents the investment value at the end of each year.
        - It is calculated as: (`Initial Investment` + `Annual Investment`) + (`Investment Value (previous year)` * `Expected Return %`) 
        - For the 2nd year onwards, the previous year's `Investment Value` replaces the `Initial investment` in the calculation.
    - `Interest (Year)`: Represents the interest earned in the current year.
        - It is calculated as: `Investment Value (previous year)` * `Expected Return %`.
    - `Total Interest`: Displays the cumulative interest values earned as the `Year` increases.
        - It is calculated as: `Investment Value` - `Initial Investment` - (`Annual Investment` * `year`)
    - `Invested Capital`: Represents the total amount of contribution for the given year.
        - It is calculated as: `Investment Value` - `Total Interest`

- Finally, we add `<Results input={userInput} />` into `App.jsx` to showcase the calculated table results

- Additonal improvement:
    - Add `const inputIsValid = userInput.duration >= 1;` and update `{inputIsValid && <Results input={userInput} />}` in `App.jsx` so that the program will not crash if the user input is less than or equal to 0 for duration value. 
