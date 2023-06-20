
CREATE TABLE WashingMachines
(
    Id int primary key,
    Identifier text not null,
    SerialId text not null,
    NozzleDiameterMM int default 0,
    TankId integer not null,
    RunningTimeSinceLastService real default 0.0,
    LifeRunningTime real default 0.0,
    MachineTypeId integer not null
);    


CREATE TABLE CleaningMediaTypes
(
    Id integer primary key autoincrement,
    Name text not null
);


CREATE TABLE WashingRuns
(
    Id integer primary key autoincrement,
    WashingMachineId int references WashingMachines(Id),
    Status int not null,
    WashType int not null,
    StartDateTime real default 0.0,
    EndDateTime real default 0.0,
    CleaningMediaId int references CleaningMediaTypes(Id),
    BatchGUID text,
    SystemCargoId int default 0,
    CargoDisplayName text,
    WaterCost real default 0.0,
    EnergyCost real default 0.0,
    MoneyCost real default 0.0
);

/*
CREATE TABLE WashingMachineParameters
(
    MachineTypeId int not null,
    NozzleMM real not null,
    A_value real not null,
    K_value real not null,
    CONSTRAINT wmParams_PK PRIMARY KEY (MachineTypeId, NozzleMM)
);
*/



    