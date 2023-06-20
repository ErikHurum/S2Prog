
-- ** Washing machines **
/*INSERT INTO WashingMachines(Id, Identifier, SerialId, NozzleDiameterMM, TankId, RunningTimeSinceLastService, LifeRunningTime) 
VALUES 
(74776576, 'SC30H-RC-1', 'SC30HRC-9990', 6, 68812801, 0.0, 0.0),
(74776576, 'SC30H-RC-2', 'SC30HRC-9991', 9, 68812801, 0.0, 0.0),
(74776576, 'SC30H-RC-3', 'SC30HRC-9992', 8, 68812802, 18000, 0.0),
(2144444003, 'SC30H-RC-4', 'SC30HRC-9993', 8, 68812802, 36000, 720000.0);
*/
-- ** Cleaning media types **
INSERT INTO CleaningMediaTypes(Name)
VALUES 
('Seawater'),
('Cleaning media A'), 
('Cleaning media B'), 
('Cleaning media C');


-- ** Washing machine Runs **
--YYYY-MM-DD HH:MM:SS.SSS
INSERT INTO WashingRuns(WashingMachineId, Status, WashType, StartDateTime, EndDateTime, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName,  WaterCost, EnergyCost, MoneyCost) 
VALUES 
-- Running or idle runs:
(74776576, 2, 2, strftime('%s','2012-02-01 12:01:02.000'), NULL, 1, '9AA5747BF6A04EDFAE940C4B5EE5EECE', 1, 'Diesel', 30.0, 40.0, 50.0),
(74776576, 2, 0, strftime('%s','2013-02-05 12:01:02.000'), NULL, 2, '64857CDE27824654BF070884989147F7', 1, 'Petroleum', 35.0, 45.0, 55.0),
(74776576, 2, 1, strftime('%s','2012-01-01 12:01:02.000'), NULL, 0, '563999A5565E44E2B216BFF1859CFE34', 1, 'Jet A', 5.0, 10.0, 15.0),
(74776577, 3, 2, strftime('%s','2012-02-01 12:01:05.000'), strftime('%s','2012-02-01 13:01:05.000'), 1, '9AA5747BF6A04EDFAE940C4B5EE5EECE', 1, 'Diesel', 30.0, 40.0, 50.0),
(74776577, 3, 2, strftime('%s','2013-02-05 12:01:02.000'), strftime('%s','2013-02-05 14:01:02.000'), 2, '64857CDE27824654BF070884989147F7', 1, 'Petroleum', 35.0, 45.0, 55.0), 
(74776578, 1, 1, strftime('%s','2012-01-15 12:01:02.000'), NULL, 3, 'C96E44DA1EA54641903237CD27266F6D', 1, 'Jet A', 25.0, 210.0, 215.0),
(74776578, 2, 1, strftime('%s','2013-01-29 12:01:02.000'), NULL, 2, 'D530AF4858CB46B0B835EC2A853F92D8', 1, 'Petroleum', 5.0, 10.0, 15.0),
(74776579, 3, 2, strftime('%s','2012-01-15 12:30:02.000'), strftime('%s','2012-01-15 13:35:00.000'), 3, 'C96E44DA1EA54641903237CD27266F6D', 1, 'Jet A', 25.0, 210.0, 215.0),

-- a completed run batch in tank 1:
(74776576, 1, 2, strftime('%s','2013-02-18 16:00:00.000'), strftime('%s','2013-02-18 17:30:00.000'), 1, '76C2B1CA00794DF38FCA5DA92C5148B7', 1, 'Petroleum', 25.0, 35.0, 45.0),
(74776577, 1, 2, strftime('%s','2013-02-18 16:05:00.000'), strftime('%s','2013-02-18 17:35:00.000'), 1, '76C2B1CA00794DF38FCA5DA92C5148B7', 1, 'Petroleum', 25.0, 35.0, 45.0),

-- completed run batch in tank 2, non-specified cargo
(74776578, 1, 2, strftime('%s','2013-02-19 15:30:00.000'), strftime('%s','2013-02-18 17:00:00.000'), 2, '6CC020AB58624422B7862BF04E3A08E2', 0, NULL, 25.0, 35.0, 45.0),
(74776579, 1, 2, strftime('%s','2013-02-19 16:00:00.000'), strftime('%s','2013-02-18 17:30:00.000'), 2, '6CC020AB58624422B7862BF04E3A08E2', 0, NULL, 25.0, 35.0, 45.0);


/*
INSERT INTO WashingMachineParameters(MachineTypeId, NozzleMM, A_value, K_value)
VALUES
(100, 60, 0.5, 0.25),
(100, 70, 1.8, 0.28),
(100, 80, 2.9, 0.31),
(100, 90, 4.0, 0.36),
(100, 100, 5.0, 0.40),
(100, 110, 6.3, 0.55),
(100, 120, 7.4, 0.68);
*/



