create table doctor(
    ssn varchar2(5) primary key,
    FirstName varchar2(15) not null,
    LastName varchar2(15) not null,
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
    ssn varchar2(5) check (ssn like 'P%') primary key,
    FirstName varchar2(15) not null,
    LastName varchar2(15) not null,
    address varchar2(20),
    dob date,
    primary_doctor_ssn varchar2(5) references doctor(ssn) on delete cascade
);

insert all
    into patient values ('P001', 'Sayantan', 'Sarkar', 'Lahore', to_date('29-02-1948', 'DD-MM-YYYY'), 'D001')
    into patient values ('P002', 'Arpan', 'Kundu', 'Bora', to_date('05-04-2002', 'DD-MM-YYYY'), 'D001')
    into patient values ('P003', 'Sayan', 'Pal', 'Kalachhara', to_date('16-11-2003', 'DD-MM-YYYY'), 'D005')
    into patient values ('P004', 'Souhit', 'Paul', 'Baruipara', to_date('10-08-2002', 'DD-MM-YYYY'), 'D002')
    into patient values ('P005', 'Ajay', 'Bag', 'Krishnarampur', to_date('01-01-1977', 'DD-MM-YYYY'), 'D001')
select * from dual;

create table medicine(
    TradeName varchar2(10) primary key,
    UnitPrice number(5,2) not null,
    GenericFlag varchar2(1) check (genericflag in ('Y', 'N')) 
);

insert all
	into medicine values ('Aspirin', '10.50', 'Y')
	into medicine values ('Vitamin', '5.00', 'Y')
	into medicine values ('ORS', '7.00', 'N')
	into medicine values ('RantacD', '3.50', 'Y')
	into medicine values ('Pyrigesic', '2.50', 'Y')
select * from dual;

create table prescription(
    Id varchar2(5) check (Id like 'PR%') primary key,
    Doctor_ssn varchar2(5) references doctor(ssn) on delete cascade,
    Patient_snn varchar2(5) references patient(ssn) on delete cascade
);

insert all
    into prescription values ('PR001', 'D001', 'P001')
    into prescription values ('PR002', 'D001', 'P002')
    into prescription values ('PR003', 'D001', 'P005')
    into prescription values ('PR004', 'D002', 'P004')
    into prescription values ('PR005', 'D003', 'P001')
    into prescription values ('PR006', 'D004', 'P002')
    into prescription values ('PR007', 'D005', 'P003')
select * from dual;

create table Prescription_Medicine(
    Prescription_Id varchar2(5) references prescription(Id) on delete cascade,
    TradeName varchar2(10) references medicine(tradename) on delete cascade,
    NumOfUnits number(5),
    primary key (Prescription_Id, TradeName)
);

insert all
    into Prescription_Medicine values ('PR001', 'Aspirin', 2)
    into Prescription_Medicine values ('PR001', 'Vitamin', 1)
    into Prescription_Medicine values ('PR002', 'RantacD', 10)
    into Prescription_Medicine values ('PR003', 'Pyrigesic', 5)
    into Prescription_Medicine values ('PR003', 'RantacD', 5)
    into Prescription_Medicine values ('PR004', 'ORS', 4)
    into Prescription_Medicine values ('PR005', 'Aspirin', 3)
    into Prescription_Medicine values ('PR006', 'Vitamin', 7)
    into Prescription_Medicine values ('PR007', 'ORS', 6)
select * from dual;

create table SeniorD(
    ssn varchar2(5) primary key,
    TLicence varchar2(10),
    foreign key (ssn) references doctor(ssn) on delete cascade
);

create table JuniorD(
    ssn varchar2(5) primary key,
    TStart date,
    TEnd date,
    foreign key (ssn) references doctor(ssn) on delete cascade
);

insert all
    into SeniorD values ('D001', 'TL001')
    into SeniorD values ('D002', 'TL002')
    into JuniorD values ('D003', to_date('01-01-2025', 'DD-MM-YYYY'), to_date('31-12-2025', 'DD-MM-YYYY'))
    into JuniorD values ('D004', to_date('01-01-2025', 'DD-MM-YYYY'), to_date('31-12-2025', 'DD-MM-YYYY'))
    into JuniorD values ('D005', to_date('01-01-2024', 'DD-MM-YYYY'), to_date('31-12-2024', 'DD-MM-YYYY'))
    into JuniorD values ('D006', to_date('01-01-2024', 'DD-MM-YYYY'), to_date('31-12-2024', 'DD-MM-YYYY'))
select * from dual;

-- 1. List the trade name of generic medicine with unit price less than $50.
select tradename from medicine where genericflag = 'Y' and unitprice < 50;

-- 2. List the first and last name of patients whose primary doctor named ʻJohn Smithʼ.
select d.firstname, d.lastname from 
    doctor d join patient p on d.ssn = p.primary_doctor_ssn 
    where d.firstname = 'John' and d.lastname = 'Smith';

-- 3. List the first and last name of doctors who are not primary doctors to any patient.
select d.firstname, d.lastname from doctor d 
    where ssn not in (select primary_doctor_ssn from patient);

-- 4. For medicines written in more than 20 prescriptions, report the trade name and the total number of units prescribed.
select tradename from 
    (select tradename, count(prescription_id) as count 
    from prescription_medicine group by tradename)
    where count > 20;

-- 5. List the SSN of patients who have ʻAspirinʼ and ʻVitaminʼ trade names in one prescription.
select patient_ssn from prescription where id in 
    (select prescription_id from prescription_medicine 
    where tradename = 'Aspirin' or tradename = 'Vitamin' 
    group by prescription_id having count(*)>1);

-- 6. List the SNN of distinct patients who have ʻAspirinʼ prescribed to them by doctor named ʻJohn Smithʼ.
select distinct p.patient_ssn from 
    doctor d join prescription p on d.ssn = p.doctor_ssn 
    join prescription_medicine pm on p.id = pm.prescription_id 
    where d.firstname='John' and d.lastname='Smith' and tradename='Aspirin';

-- 7. List the first and last name of patients who have no prescriptions written by doctors other than their primary doctors.
select p.firstname, p.lastname 
    from patient p where ssn not in (
        select patient_ssn from prescription 
        where doctor_ssn != p.primary_doctor_ssn
    );