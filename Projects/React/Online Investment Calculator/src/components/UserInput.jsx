import { useState } from 'react';

export default function UserInput({ onChange }) {
    // Local state to manage user inputs (if not managed by parent)
    const [userInput, setUserInput] = useState({
        initialInvestment: '10000',
        annualInvestment: '1200',
        expectedReturn: '7',
        duration: '12'
    });

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
                <p>
                    <label>Annual Investment (USD$)</label>
                    <input
                        type='number'
                        required
                        value={userInput.annualInvestment}
                        onChange={(event) => handleInputChange('annualInvestment', event.target.value)}
                    />
                </p>
            </div>

            <div className='input-group'>
                <p>
                    <label>Expected Return (%)</label>
                    <input
                        type='number'
                        required
                        value={userInput.expectedReturn}
                        onChange={(event) => handleInputChange('expectedReturn', event.target.value)}
                    />
                </p>
                <p>
                    <label>Duration (years)</label>
                    <input
                        type='number'
                        required
                        value={userInput.duration}
                        onChange={(event) => handleInputChange('duration', event.target.value)}
                    />
                </p>
            </div>
        </section>
    );
}
