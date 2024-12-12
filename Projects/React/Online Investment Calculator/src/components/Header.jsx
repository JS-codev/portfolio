import logo from '../assets/investment-logo.png';
export default function Header() {
    return <header id='header'>
        <img src={logo} alt=' Investment logo ' />
        <h1>Online Investment Calculator</h1>
    </header>
}