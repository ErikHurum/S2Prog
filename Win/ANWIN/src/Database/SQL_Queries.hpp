#pragma once

#include <vector>
namespace queries {

const AnsiString InitialWashRuns(void) {
    return "SELECT A.Identifier, A.TankName, B.Name, C.WashingMachineId,C.StartDateTime, C.EndDateTime,C.WashTypeName, B.Name,"
           "C.WaterConsumption, C.EnergyConsumption, C.FuelConsumption, C.Flow, C.RunTime, C.BatchGUID"
           " FROM( "
           " (SELECT WashingMachineId,StartDateTime,EndDateTime, CleaningMediaId,Status,WaterConsumption, EnergyConsumption, FuelConsumption, Flow,BatchGUID,"
           " (RunningTime/3600) || ':' || strftime('%M:%S',RunningTime/86400.0) AS RunTime,"
           " CASE WashType WHEN 0 THEN 'Unknown' WHEN 1 THEN 'PreWash' WHEN 2 THEN 'Wash' ELSE 'Error' END WashTypeName FROM WashingRuns) C" 
           " INNER JOIN"
		   " (SELECT Id, Identifier, TankId, TankName FROM WashingMachines) A ON A.Id=C.WashingMachineId"
		   " LEFT JOIN"
           " (SELECT Id, Name FROM CleaningMediaTypes ) B ON B.Id=C.CleaningMediaId"
           " ) WHERE  (C.Status=1 OR C.Status = 3 ) AND C.StartDateTime >= 1631272779 order by A.Id desc";
}


const AnsiString WashRunsTank(int TankId, long StartTime, long StopTime) {
    return "SELECT A.Identifier, A.TankName, B.Name, C.WashingMachineId,C.StartDateTime, C.EndDateTime,C.WashTypeName, B.Name,"
           "C.WaterConsumption, C.EnergyConsumption, C.FuelConsumption, C.Flow, C.RunTime, C.BatchGUID"
           " FROM( "
           " (SELECT WashingMachineId,StartDateTime,EndDateTime, CleaningMediaId,Status,WaterConsumption, EnergyConsumption, FuelConsumption, Flow,BatchGUID,"
           " (RunningTime/3600) || ':' || strftime('%M:%S',RunningTime/86400.0) AS RunTime," 
           " CASE WashType WHEN 0 THEN 'Unknown' WHEN 1 THEN 'PreWash' WHEN 2 THEN 'Wash' ELSE 'Error' END WashTypeName FROM WashingRuns) C" 
           " INNER JOIN"
		   " (SELECT Id, Identifier, TankId, TankName FROM WashingMachines) A ON A.Id=C.WashingMachineId"
		   " LEFT JOIN"
           " (SELECT Id, Name FROM CleaningMediaTypes ) B ON B.Id=C.CleaningMediaId"
           " ) WHERE TankId = "+AnsiString(TankId)+" AND"
           " (C.Status=1 OR C.Status = 3 ) AND C.StartDateTime >= "+AnsiString(StartTime)+" AND C.EndDateTime <=  "+AnsiString(StopTime)+"  order by A.Id desc";
}


const AnsiString WashRuns(long StartTime, long StopTime) {
	return "SELECT A.Identifier, A.TankName, B.Name, C.WashingMachineId,C.StartDateTime, C.EndDateTime,C.WashTypeName, B.Name,"
		   "C.WaterConsumption, C.EnergyConsumption, C.FuelConsumption, C.Flow, C.RunTime, C.BatchGUID"
		   " FROM( "
		   " (SELECT WashingMachineId,StartDateTime,EndDateTime, CleaningMediaId,Status,WaterConsumption, EnergyConsumption, FuelConsumption, Flow,BatchGUID,"
		   " (RunningTime/3600) || ':' || strftime('%M:%S',RunningTime/86400.0) AS RunTime,"
		   " CASE WashType WHEN 0 THEN 'Unknown' WHEN 1 THEN 'PreWash' WHEN 2 THEN 'Wash' ELSE 'Error' END WashTypeName FROM WashingRuns) C"
		   " INNER JOIN"
		   " (SELECT Id, Identifier, TankId, TankName FROM WashingMachines) A ON A.Id=C.WashingMachineId"
		   " LEFT JOIN"
		   " (SELECT Id, Name FROM CleaningMediaTypes ) B ON B.Id=C.CleaningMediaId"
		   " ) WHERE "
		   " (C.Status=1 OR C.Status = 3 ) AND C.StartDateTime >= "+AnsiString(StartTime)+" AND C.EndDateTime <=  "+AnsiString(StopTime)+"  order by A.Id desc";
}

const AnsiString WashRunsBatchGUId(AnsiString BatchGUID, int StartTime, int StopTime) {
    return "SELECT MAX(m.TankId), MAX(r.Status), MAX(r.WashType), MAX(r.CleaningMediaId), MAX(r.BatchGUID), MIN(r.StartDateTime) as startDT, MAX(r.EndDateTime) as endDT, MAX(SystemCargoId), "
           " IFNULL(CargoDisplayName, 'Not specified'), "
           "SUM(r.WaterConsumption), SUM(r.EnergyConsumption), SUM(r.FuelConsumption), MAX(r.RunningTime) "
           "FROM WashingRuns r INNER JOIN WashingMachines m ON r.WashingMachineId = m.Id "
		   "WHERE r.BatchGUID LIKE '"+BatchGUID+"' ";

}


}
/*
SELECT A.Identifier, A.TankName, B.Name, C.WashingMachineId,
C.StartDateTime, C.EndDateTime,C.WashTypeName, B.Name,
C.WaterConsumption, C.EnergyConsumption, C.FuelConsumption, C.Flow 
FROM( 
(SELECT WashingMachineId,StartDateTime,EndDateTime, CleaningMediaId,Status,WaterConsumption, EnergyConsumption, FuelConsumption, Flow, 
CASE WashType WHEN 0 THEN 'Unknown' WHEN 1 THEN 'PreWash' WHEN 2 THEN 'Wash' ELSE 'Error' END WashTypeName FROM WashingRuns) C 
INNER JOIN
(SELECT Id, Identifier, TankId, TankName FROM WashingMachines) A ON A.Id=C.WashingMachineId
INNER JOIN
(SELECT Id, Name FROM CleaningMediaTypes ) B ON B.Id=C.CleaningMediaId 

) WHERE 
A.TankId == 68812801 AND (C.Status=1 OR C.Status = 3 ) AND C.StartDateTime >=1631022755 AND C.EndDateTime <=  1632999159  order by A.Id desc
*/
