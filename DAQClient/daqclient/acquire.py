from __future__ import annotations

import argparse
from pathlib import Path
from typing import Optional, TYPE_CHECKING
if TYPE_CHECKING:
    import numpy as np
from typing import NamedTuple

from tango import AttributeProxy, EventType, DataReadyEventData

import imageio

TANGO_HOST = "tango://localhost:10000"

class DeviceImageAcquireProperties(NamedTuple):
    attribute_proxy: AttributeProxy
    save_folder: Optional[Path] = None

class Acquirer:
    def __init__(self, device_handles: list[str], save_folder: Optional[Path] = None):
        """
        Parameters
        ----------
        device_list : list[str]
            list of Tango handles that this Client will subscribe to
        save_folder : str
            Top level folder for all devices' images. If not given, don't save images.
            Images are saved in <save_folder>/<device_handle>/0123.tiff
        """

        self.device_image_acquire_properties = {}

        for device_handle in device_handles:
            
            self.device_image_acquire_properties[device_handle] = DeviceImageAcquireProperties(
                AttributeProxy(f"{TANGO_HOST}/{device_handle}/DynamicImage"), 
            )

            # save folder for this device
            if save_folder is not None:
                self.device_image_acquire_properties[device_handle].save_folder = save_folder / Path(device_handle)
                self.device_image_acquire_properties[device_handle].save_folder.mkdirs(exist_ok=True, parents=True)

            # subscribe to the image attributes' data ready events
            self.device_image_acquire_properties[device_handle].attribute_proxy.subscribe_event(EventType.DATA_READY_EVENT, self.handle_data_ready_event)
            print(self.device_image_acquire_properties[device_handle].attribute_proxy.name())

    def handle_data_ready_event(self, event: DataReadyEventData):
        """
        Parameters
        ----------
        event : DataReadyEventData
            DataReady event data
        """
        device_handle = event.device.dev_name()
        print(f"Received data ready event from {device_handle}")
        
        # get image from device
        image: np.ndarray = event.device.read_attribute(event.attr_name)
        print(f"Received image with shape {image.shape}")

        if self.device_image_acquire_properties[device_handle].save_folder:
            imageio.imwrite(self.device_image_acquire_properties[device_handle].save_folder / f"{event.ctr:04d}.tiff", image)

    def run(self):
        while True:
            pass


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(
        usage="python -m daqclient.acquire device1[, device2[, device3 ...]] [--save-folder /path/to/folder]",
        description="Listens to events and passes them on to processing.",
    )
    argparser.add_argument("device_list", nargs="+", help="One or more Tango device handles")
    argparser.add_argument("--save-folder", dest="save_folder", help="Top level folder for all devices' images. If not given, don't save images.", type=Path)
    args = argparser.parse_args()

    acquirer = Acquirer(args.device_list, args.save_folder)
    acquirer.run()
