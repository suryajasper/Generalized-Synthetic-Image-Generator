from PIL import Image
import sys, os

path = os.path.abspath("") + "/";
processed = False

def processImage(path, name):
	img = Image.open(os.path.join(path, name))
	size = img.size[0] / 4 # splits the width of the image by 3, expecting the 3x2 layout blender produces.
	splitAndSave(img, 2, 1, size, addToFilename(name, "_right"))
	splitAndSave(img, 0, 1, size, addToFilename(name, "_left"))
	splitAndSave(img, 1, 1, size, addToFilename(name, "_front"))
	splitAndSave(img, 3, 1, size, addToFilename(name, "_back"))
	splitAndSave(img, 1, 0, size, addToFilename(name, "_up"))
	splitAndSave(img, 1, 2, size, addToFilename(name, "_down"))

def addToFilename(name, add):
	name = name.split('.')
	return name[0] + add + "." + name[1]

def splitAndSave(img, startX, startY, size, name):
	startX *= size
	startY *= size
	area = (startX, startY, startX + size, startY + size)
	saveImage(img.crop(area), path, name)

def saveImage(img, path, name):
	try:
		img.save(os.path.join(path, name))
	except:
		print("*   ERROR: Could not convert image.")
		pass

for arg in sys.argv:
	if ".png" in arg or ".jpg" in arg:
		processImage(path, arg)
		processed = True

if not processed:
	print("*  ERROR: No Image")
	print("   usage: 'python script.py image-name.png'")