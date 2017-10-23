#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @time    : 2017/10/23 19:15
# @author  : 
# @description:

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

if __name__ == "__main__":
    chromePath = r'G:\chromedriver_win32\chromedriver.exe'
    browser = webdriver.Chrome(chromePath)
    url = "https://www.bing.com/"
    browser.get(url)
    inputEditer = browser.find_element_by_id("bgDiv")
    inputEditer.send_keys("python selenum webdirver download")
    time.sleep(1)
    inputEditer.send_keys(Keys.RETURN)
    time.sleep(5)
    browser.close()