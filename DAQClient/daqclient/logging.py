import logging
import logging.config
from pathlib import Path

# put logs in UT3_Control_And_Data_Acquisition_System/log
LOG_FOLDER = Path(__file__).parents[2] / 'log'

LOGGING_CONFIG = {
    "version": 1, 
    "formatters": {
        "time_source_level_message": {
            "format": "{asctime}\t{name}:{levelname}\t{message}",
            "style": "{",
            "validate": False
        }
    },
    "filters": {},
    "handlers": {
        "acquire_file_handler": {
            "class": "logging.FileHandler",
            "level": "ERROR",
            "formatter": "time_source_level_message",
            "filename": str(LOG_FOLDER / "acquire.log"),
        },
        "acquire_stream_handler": {
            "class": "logging.StreamHandler",
            "level": "INFO",
            "formatter": "time_source_level_message",
            "stream": "ext://sys.stdout",
        }
    },
    "loggers": {
        "acquire": {
            "level": "INFO",
            "propagate": False,
            "handlers": [
                "acquire_file_handler",
                "acquire_stream_handler",
            ]
        },
    },
    "root": {
        "level": "ERROR",
        "handlers": []
    }
}

LOGGING_IS_CONFIGURED = False

def get_logger(name: str) -> logging.Logger:
    # configure logging
    global LOGGING_IS_CONFIGURED
    if not LOGGING_IS_CONFIGURED:
        logging.config.dictConfig(LOGGING_CONFIG)
        LOGGING_IS_CONFIGURED = True

    return logging.getLogger(name)
