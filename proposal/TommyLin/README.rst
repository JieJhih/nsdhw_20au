============================
Digital Image Focus Stacking
============================

Wiki: A digital image processing technique which combines multiple images taken
at different focus distances to give a resulting image with a greater depth of
field (DOF) than any of the individual source images.


Basic Information
=================

Git hub repository:
https://github.com/TommyLin/focus-stacking


Problem To Solve
================

When macro photography, the short depth of field (DOF) makes clear image only
in a small area because of very short distance to subject. To get a clear
(focused) image in a wide range, the photographer can shrink and use small
aperture size. But shrinking aperture size has two side effects as follow:

* 1. Increase diffraction effect that causes image blurry
* 2. Decrease exposure energy that makes noise relatively increase

So there are limits to get a clear photo by just shrinking aperture with one 
shot. Here are three photos to show the effect of aperture size.

+-------------------------------------+-------------------------------------+------------------------------------+
| .. image:: wiki/Dof_blocks_f1_4.jpg | .. image:: wiki/Dof_blocks_f4_0.jpg | .. image:: wiki/Dof_blocks_f22.jpg |
| Aperture=/1.4, DOF=0.8cm            | Aperture=f/4.0, DOF=2.2cm           | Aperture=f/22, DOF=12.4cm          |
+-------------------------------------+-------------------------------------+------------------------------------+
*. Source: https://en.wikipedia.org/wiki/Depth_of_field

Definition of depth of field (DOF)

.. image:: DOF_equation.png

+--------+----------------------+--------------------------------+
| Symbol | Definition           | Example                        |
+========+======================+================================+
| c      | circle of confusion  | Canon APS-C camera CoC=0.018mm |
+--------+----------------------+--------------------------------+
| f      |  focal length        | EF100mm f/2.8L MACRO IS USM    |
+--------+----------------------+--------------------------------+
| N      |  f-number            | f/2.8, f/4, f/10, f/16         |
+--------+----------------------+--------------------------------+
| u      |  distance to subject | 5cm ~ 20cm for Camera          |
+--------+----------------------+--------------------------------+
For example: A Canon APS-C camera with conditions in previous will result:

**DOF = 0.36mm**, (assume N=10, u=10cm=100mm)

Fortunately, photographer can take multiple **"digital"** photos and stack these
photos together to make a focused photo in large area.

+-------------------------------------------------------+
| .. image:: wiki/750px-Focus_stacking_Tachinid_fly.jpg |
+-------------------------------------------------------+
*. Source: https://en.wikipedia.org/wiki/Focus_stacking


Algorithm
=========

Edge detection
______________

Pixel values change fast (sharp) in the focused area. Pixel values chage gentlely
(soft) in the defocused aread. The sharp aread consider as edge that pixel value
varies fast. Follow steps aim to find the edges in a photo.

1. Perform a **Gaussian blur** on image with following kernel:

::

   1  2  1
   2  4  2
   1  2  1

2. Perform a **Laplacian Edge Detection kernel** on Gaussian Blurred image:

::

   -1 -1 -1
   -1  8 -1
   -1 -1 -1

3. Take absolute value of Laplacian of Gaussian (LoG) result. This will quantify
   the strength of edges with respect to the size and strength of kernel.
4. Create a blank image, loop through each pixel and find the strongest edge in
   the LoG(i.e. the highest value in the image stack) and take the RGB value for
   that pixel from the corresponding image.

Structural Similarity Index Measure (SSIM)
__________________________________________
The structural similarity index measure (SSIM) is a method for predicting the
perceived quality of digital television and cinematic pictures, as well as other
kinds of digital images and videos. SSIM is used for measuring the similarity
between two images.

.. image:: https://wikimedia.org/api/rest_v1/media/math/render/svg/1783c17346b8f4c822ed206798bb6769a845c417


Prospective Users
=================

Macro photography and optical microscopy users.


System Architecture
===================

1. Input: Directory that store images with different focus distance.
2. Read image from files
3. Gaussian blur
4. Laplacian Edge Detection
5. Image stacking


API Description
===============

Show how your system can be programmed.  You are supposed to implement the
system using both C++ and Python.  Describe how a user writes a script in the
system.

Auto scan mode: Users select specific directory that contain photos. The system 
will scan directory and determinate the groups of photos.


Engineering Infrastructure
==========================

To evaluate the algorism performance, this project will create images from a
focused image. Through these image 

1. Get a clear and focused source image (image1)
2. Divide source image into serveral sections and blur with Gaussian smoothing
3. Through the focus stacking API to combine these blurred imaged (image2)
4. Calculate SSIM of image1 and image2


Schedule
========

* Week 1: [Python] Generate defocused photos
* Week 2: [C++] Evaluate SSIM of two photos
* Week 3: [Python] Setup testing environment
* Week 4: [Python] Browse directory and read image
* Week 5: [C++] Gaussian blur & Laplacian edge detection
* Week 6: [C++] Image stacking
* Week 7: [Python/C++] Debug and optimization
* Week 8: Github CI


References
==========

1. https://en.wikipedia.org/wiki/Focus_stacking
2. https://en.wikipedia.org/wiki/Depth_of_field
3. https://en.wikipedia.org/wiki/Circle_of_confusion
4. https://en.wikipedia.org/wiki/Structural_similarity
