use UT3Data;

create table ShotRecord
(
    ShotID                int unsigned auto_increment comment 'Unique shot ID'
        primary key,
    Timestamp             bigint unsigned not null comment 'Linux timestamp of event',
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
    TopViewND             float           null comment 'Filter ND on plasma channel top view camera',
    Notes                 varchar(200)    null comment 'Notes on shot',
    BasePath              varchar(100)    null comment 'Base path to the images',
    TANGO_WFS                   varchar(100)    null comment 'Relative path to TANGO_WFS image',
    Topview               varchar(100)    null comment 'Relative path to plasma channel top view image',
    PointingScreen        varchar(100)    null comment 'Relative path to pointing screen images',
    ESpecScreenA          varchar(100)    null comment 'Relative path to electron spectrometer screen A',
    ESpecScreenB          varchar(100)    null comment 'Relative path to electron spectrometer screen B',
    PointingScreenBrem    varchar(100)    null comment 'Relative path to pointing screen for Bremsstrahlung'
)
    comment 'Shot record';

