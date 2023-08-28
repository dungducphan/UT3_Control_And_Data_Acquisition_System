from __future__ import annotations

import argparse

from tango import AttributeProxy, EventType, DataReadyEventData


class Acquirer:
    def __init__(self, device_list: list[str]):
        """
        Parameters
        ----------
        device_list : list[str]
            list of Tango handles that this Client will subscribe to
        """

        self.image_attributes = [
            AttributeProxy(f"{device}/DynamicImage")
            for device in device_list
        ]

        # subscribe to the image attributes' data ready events
        for image_attr in self.image_attributes:
            image_attr.subscribe_event(EventType.DATA_READY_EVENT, self.handle_data_ready_event)
            print(image_attr.name())

    def handle_data_ready_event(self, event: DataReadyEventData):
        """
        Parameters
        ----------
        event : DataReadyEventData
            DataReady event data
        """
        print(f"Received data ready event from {event.device.name}")

    def run(self):
        while True:
            '''
                TODO: wait for events and handle them: check the image size send from server 
            '''


if __name__ == '__main__':
    argparser = argparse.ArgumentParser(
        usage="python -m daqclient.acquire device1[, device2[, device3 ...]]",
        description="Listens to events and passes them on to processing.",
    )
    argparser.add_argument("device_list", nargs="+", help="One or more Tango device handles")
    args = argparser.parse_args()

    acquirer = Acquirer(args.device_list)
    acquirer.run()
