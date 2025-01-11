https://github.com/user-attachments/assets/9345ad15-cd75-489e-a50d-6cfee07751eb


**Explanation:**
**Step 1: Add header & requried image **
- Put image under src/assets/image.png

- We create a `Header.jsx` for title (under `Src` > `components` folder)
- `index.css` file contains `#header` style that has `text-align: center`
`index.css` contains global styles that can be applied to define overall styling of an app. This styling for elements includes body, headings, link, container styles. 

```js filename=Header.jsx
import logo from '../assets/investment-calculator-logo.png';
export default function Header() {
    return (
    <header id='header'> 
    {/* Above id applies text-align: center that will move title to center*/}
        <img src={logo} alt='Logo showing money bag :D' />
        <h1>Investment Calculator</h1>
    </header>
}
```

- We then add Header file component into `App.jsx` for it to open
  - App.jsx is the top-level component in React. It defines the layout of an app and includes other components that make up the user interface (UI).

```js filename=App.jsx
import Header from './components/Header.jsx';
function App() {
    return (    
        <Header />
        )
}
export default App
```
**Step 2: Adding and updating user input **
- Create `UserInput.jsx` that returns a section that takes in user-input in numerical for varibles of `initialInvestment`, `annualInvestment`, `expectedReturn`, and `duration`. 
    - `initialInvestment` represents the amount of money initially invested/deposited at the start of the investment.
    - `annualInvestment` indicates the additional amount of money contributed to the investment annually.
    - `expectedReturn` represents the  expected annual rate of return on the investment (%)
    - `duration` represents the duration of the investment in years.


```jsx filename="UserInput.jsx"
export default function UserInput({ onChange }) {
    // Local state to manage user inputs (if not managed by parent)
    const [userInput, setUserInput] = useState({
        initialInvestment: '10000',
        annualInvestment: '1200',
        expectedReturn: '7',
        duration: '12'
    });
 ```
