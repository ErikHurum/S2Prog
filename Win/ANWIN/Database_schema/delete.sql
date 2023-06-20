

DELETE FROM WashingRuns;

DELETE FROM CleaningMediaTypes;

DELETE FROM WashingMachines;

-- reset autoincrements:
UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE name = 'CleaningMediaTypes';

UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE name = 'WashingRuns';