Dependencies:
=============
gcc <br>
make <br>
pkg-config <br>
opencv 2.4.3 <br>
yaml=cpp 0.3 (0.5 does not work) <br>

Compilation:
============
make

Usage:
======
./main arguments

Arguments:
----------
-g	--gui			<br>
Show graphical output. <br>
-w	--write		<br>
Write each processed frame to the disk. <br>
-c  --cam			camera number	<br>
Use specified webcam. <br>
-f	--file		filename <br>
Use specified filename.
-h	--host		hostname	<br>
Send output to specified host IP.
