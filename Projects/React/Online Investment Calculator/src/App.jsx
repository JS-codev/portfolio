import { useState } from 'react';

import Header from './components/Header.jsx';
import UserInput from './components/UserInput.jsx';
import Results from './components/Results.jsx';
function App() {
    const [userInput, setUserInput] = useState({
        initialInvestment: 10000,
        annualInvestment: 1200,
        expectedReturn: 7,
        duration: 10
    });

    {/*Prevent crash from happening when user enter 0*/ }
    const inputIsValid = userInput.duration >= 1;

    function handleChange(inputIdentifier, newValue) {
        setUserInput(prevUserInput => {
            return {
                ...prevUserInput,
                [inputIdentifier]: +newValue, //add plus here to update new results
            };
        });
    } 

    return (
        <>
            <Header />
            <UserInput userInput={userInput} onChange={handleChange} />
            {!inputIsValid && (<p className='center'>Please enter a duration greater than 0.</p>)}
            {inputIsValid && <Results input={userInput} />}
        </>
    );
}
export default App
