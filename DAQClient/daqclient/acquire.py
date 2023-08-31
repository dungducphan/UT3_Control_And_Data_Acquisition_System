from __future__ import annotations

import argparse
from pathlib import Path
from typing import Optional, TYPE_CHECKING
if TYPE_CHECKING:
    import numpy as np
    from tango import DataReadyEventData, EventData
from typing import NamedTuple

from tango import AttributeProxy, EventType

import imageio

from daqclient.logging import get_logger
logger = get_logger('acquire')

TANGO_HOST = "tango://localhost:10000"

class DeviceImageAcquireProperties(NamedTuple):
    attribute_proxy: AttributeProxy
    save_folder: Optional[Path] = None

class Acquirer:
    def __init__(self, device_handles: list[str], timing_unit_device_handle: str, save_folder: Optional[Path] = None):
        """
        Parameters
        ----------
        device_list : list[str]
            list of Tango handles that this Client will subscribe to
        timing_unit_device_handle : str
            Tango handle of the TimingUnit device that triggers the cameras
        save_folder : str
            Top level folder for all devices' images. If not given, don't save images.
            Images are saved in <save_folder>/<device_handle>/0123.tiff
        """

        self.device_image_acquire_properties = {}
        self.shot_number: int = 0

        # subscribe to device image Data Ready Events
        for device_handle in device_handles:
            
            self.device_image_acquire_properties[device_handle] = DeviceImageAcquireProperties(
                AttributeProxy(f"{TANGO_HOST}/{device_handle}/DynamicImage"), 
            )

            # save folder for this device
            if save_folder is not None:
                self.device_image_acquire_properties[device_handle].save_folder = save_folder / Path(device_handle)
                self.device_image_acquire_properties[device_handle].save_folder.mkdirs(exist_ok=True, parents=True)

            # subscribe to the image attribute's data ready events
            self.device_image_acquire_properties[device_handle].attribute_proxy.subscribe_event(EventType.DATA_READY_EVENT, self.handle_image_data_ready_event)
            logger.info("Subscribed to events from %(device)/%(attr)", 
                        {'device': device_handle, 
                         'attr': self.device_image_acquire_properties[device_handle].attribute_proxy.name()
                        }
                       )

        # subscribe to TimingUnit Change event
        self.shot_id_attribute_proxy = AttributeProxy(f"{TANGO_HOST}/{timing_unit_device_handle}/ShotID")
        self.shot_id_attribute_proxy.subscribe_event(EventType.CHANGE_EVENT, self.handle_shot_id_change_event)

    def handle_image_data_ready_event(self, event: DataReadyEventData):
        """
        Acquire data from the device who sent the Attribute DataReadyEvent, and
        save it to disk.
        
        Parameters
        ----------
        event : DataReadyEventData
            DataReady event data
        """
        device_handle = event.device.dev_name()
        logger.info(f"Received data ready event (type {event.__class__}) from {device_handle}")
        
        # get image from device
        image: np.ndarray = event.device.read_attribute(event.attr_name)
        logger.info(f"Received image with shape {image.shape}")

        if self.device_image_acquire_properties[device_handle].save_folder:
            imageio.imwrite(self.device_image_acquire_properties[device_handle].save_folder / f"{self.shot_number:04d}.tiff", image)


    def handle_shot_id_change_event(self, event: EventData):
        """
        Update shot_number.
        
        Parameters
        ----------
        event : EventData
            Change event data
        """        
        device_handle = event.device.dev_name()
        logger.info(f"Received change event (type {event.__class__}) from {device_handle}")

        self.shot_number = event.attr_value.value

    def run(self):
        while True:
            pass


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(
        description="Listens to events and passes them on to processing.",
    )
    argparser.add_argument("--device-list", dest='device_list', nargs="+", 
                           help="One or more Tango device handles", required=True, 
                           metavar='device'
                          )
    argparser.add_argument("--timing-device", dest='timing_device', 
                           help="Tango handle of the TimingUnit device.", 
                           required=True, metavar='timingdevice'
                          )
    argparser.add_argument("--save-folder", dest="save_folder", 
                           help="Top level folder for all devices' images. If "
                                "not given, don't save images.", 
                           type=Path, metavar="/path/to/folder"
                          )
    args = argparser.parse_args()

    acquirer = Acquirer(args.device_list, args.save_folder)
    acquirer.run()
