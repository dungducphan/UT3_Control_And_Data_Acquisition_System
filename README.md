# UT3 Control and Data Acquisition System
 [TANGO Control System and Data Aacquisition Front-End for UT3 Laboratory](https://publish.obsidian.md/ut3/Project+00+-+UT3+DAQCS/Camera+Server+Development/UT3+Front-End+CDAq)

## Dependencies:
- [TANGO control](https://tango-controls.readthedocs.io/en/latest/contents.html).
- Camera SDKs: PCO **pco.cpp**, Basler **pylon**, and FLIR **spinnaker**.
- Boost libraries: filesystem, concurrency, interprocess.
- OpenCV: for image preprocessing.
- Image format library: TIFF, PNG, JPEG.

## Build instruction:
- [Installation of TANGO on Linux](https://tango-controls.readthedocs.io/en/latest/contents.html).
- [Build instruction](https://publish.obsidian.md/ut3/Project+00+-+UT3+DAQCS/Camera+Server+Development/Build+instruction+for+CameraServer)

## Deployment instruction:
- [Deployment instruction](https://publish.obsidian.md/ut3/Project+00+-+UT3+DAQCS/Camera+Server+Development/Deployment+instruction+for+Camera+Server)

# Change logs

## 2023-08-21
- Finished basic functionality:
	- ConfigureShotMode cameras in shot mode (reveicing external trigger from timing unit) and test mode (receiving manual software trigger from clients).
	- Multithreaded: individual threads to collect acquired images while one thread to handle client requests.
	- Saving image to a specified directory. Naming convention:
		- `<TANGO_device_name>\shot_<shotID:%05d>_<millisec_linuxtimestamp>.tiff` for external trigger shots.
		- `<TANGO_device_name>\test_<shotID:%05d>_<millisec_linuxtimestamp>.tiff` for test shots.
		- Test shots do not increase the `shotID`, so operators/experts can associate the test shots with the correct external-triggered shots.
	- Froze the development with [v0.1](https://github.com/dungducphan/UT3_Control_And_Data_Acquisition_System/releases/tag/v0.1).

## 2023-08-28
Resolve some issues with the [PR](https://github.com/dungducphan/UT3_Control_And_Data_Acquisition_System/pull/1) with respect to the CameraServer:
- Build system refactoring.
- Adding new Image attribute to TANGOCamera.
- Make the new Image attribute dynamic.
- Small fix bugs and quality of life.
Approved [PR](https://github.com/dungducphan/UT3_Control_And_Data_Acquisition_System/pull/1), merged to main.
