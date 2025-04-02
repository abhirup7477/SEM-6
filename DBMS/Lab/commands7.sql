create table doctor(
ssn varchar(5) primary key,
FirstName varchar(15) not null,
LastName varchar(15) not null,
speciality varchar2(15),
YearsOfExperience number(2),
PhoneNum number(10) check (phonenum > 999999999 and phonenum < 10000000000)
);

insert all
into doctor values ('D001', 'John', 'Smith', 'Cardiologist', 25, 9876543219)
into doctor values ('D002', 'Abhirup', 'Bag', 'Neurologist', 2, 9339316128)
into doctor values ('D003', 'Arnab', 'Chattopadhyay', 'Dermatologist', 1, 6296885021)
into doctor values ('D004', 'Abhrajit', 'Rath', 'Oncologist', 1, 7477516708)
into doctor values ('D005', 'Abhishikta', 'Roy', 'Cardiologist', 2, 8972505145)
into doctor values ('D006', 'Parna', 'Roy', 'Gynologist', 2, 9782647517)
select * from dual;

create table patient(
ssn varchar(5) check (ssn like 'P%') primary key,
FirstName varchar(15) not null,
LastName varchar(15) not null,
address varchar2(20),
dob date,
primary_doctor_ssn varchar(5) references doctor(ssn) on delete cascade
);