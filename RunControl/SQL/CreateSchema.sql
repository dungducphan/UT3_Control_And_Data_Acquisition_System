use UT3Data;
create table BeamlineParameters
(
    ShotID                int unsigned auto_increment comment 'Unique shot ID'
        primary key,
    Timestamp             bigint unsigned null comment 'Linux timestamp of event',
    Date                  date            null comment 'Date of shot',
    EnergyOnTarget        float           null comment 'Laser pulse energy on target in Joules',
    FarfieldEnergy        float           null comment 'Farfield energy in mJ',
    PulseDuration         float           null comment 'Pulse duration in femtoseconds',
    GasJetBackPressure    float           null comment 'Gas jet back pressure in Bars',
    GasJetPosX            float           null comment 'Gas jet relative position (x) in microns',
    GasJetPosY            float           null comment 'Gas jet relative position (y) in microns',
    GasJetPosZ            float           null comment 'Gas jet relative position (z) in microns',
    GasJetOpeningDuration float           null comment 'Gas jet opening duration in milliseconds',
    GasJetTiming          float           null comment 'Gas jet opening to main pulse in milliseconds',
    ProbeTiming           float           null comment 'Probe to main pulse in picoseconds',
    ProbeND               float           null comment 'Filter ND on probe camera',
    WFSND                 float           null comment 'Filter ND on wavefront sensor',
    TopViewND             float           null comment 'Filter ND on plasma channel top view camera'
)
    comment 'Electron Accelerator Beamline parameters';

create table ShotRecord
(
    ShotID             int unsigned auto_increment comment 'Unique shot ID'
        primary key,
    Timestamp          bigint unsigned null comment 'Linux timestamp of event',
    Date               date            null comment 'Date of shot',
    BasePath           varchar(100)    not null comment 'Base path of the image directory',
    WFS                varchar(100)    null comment 'Path to image from wavefront sensor',
    TopView            varchar(100)    null comment 'Path to image of plasma channel top view',
    PointingScreen     varchar(100)    null comment 'Path to image of electron pointing screen',
    ESpecScreenA       varchar(100)    null comment 'Path to image from electron spectrometer screen A',
    ESpecScreenB       varchar(100)    null comment 'Path to image from electron spectrometer screen B',
    PointingScreenBrem varchar(100)    null comment 'Path to image of the second pointing screen'
)
    comment 'Actual shot data';

