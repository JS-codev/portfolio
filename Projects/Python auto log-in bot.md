**What it does:** This bot inputs your username and password automatically for you, which will help you log in easier and faster.

<ins>**How it works:**</ins>
- Once the code is excuted, the bot will automatically run based on the entire code, and will open up a website to log in automatically.

**Preview of Auto login pybot working:**
[Demostration Video](https://github.com/user-attachments/assets/acfadd57-897f-4e3a-adb6-007a194a68e2)

<ins>**Auto login pybot code:**</ins>
```
from selenium import webdriver
import time

options = webdriver.ChromeOptions()
options.binary_location = "C:\Program Files\Google\Chrome\Application\chrome.exe" #Locate your chrome
browser = webdriver.Chrome(chrome_options=options, executable_path="C:\chromedriver.exe") #Using Chromedriver to open Chrome broswer
#enter the link to the website you want to automate login.
website_link=" [Enter website link here] "

#enter your login username
username="[Enter username here]"
#enter your login password
password="[Enter password here]"

browser.get((website_link))  #bot opens Chrome browser
time.sleep(1)        #Bot waits 1 second
user_element = browser.find_element_by_id("[place id here]")
user_element.send_keys(username)
nextButton_element = browser.find_element_by_id("[place id here]")
nextButton_element.click()
time.sleep(3)
pass_element = browser.find_element_by_id("[place id here]")
pass_element.send_keys(password)
SignInButton_element=browser.find_element_by_id("[place id here]")
SignInButton_element.click()
```
---

**Detail steps to find id element in browser page:**

Open deveoper tools(F12) on any log-in website, then press ctrl + shift + C.
Click on the Username/Email element textbox, which is shown below.

![1st](https://github.com/JS-codev/portfolio/assets/174925691/428c9253-13d1-4e30-acad-309a01f2ae0d)

3. Your id element should appear somewhere in your developer tools below.

![2nd](https://github.com/JS-codev/portfolio/assets/174925691/f16f7a2e-6dd2-42d3-8c89-8b548afa2001)

4. So the id element found for "Email address" is i0118.
