import timeit


setup= """
import cv2
import segment
img = cv2.imread('webpage.png')
"""
statement = "segment.imageTest(img)"

print(f"Execution time is: {timeit.timeit(setup=setup, stmt=statement, number=1)}")
