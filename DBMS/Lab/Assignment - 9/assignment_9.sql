create table employee(
    PersonName varchar2(20) primary key,
    Street varchar2(20),
    City varchar2(20)
);

insert all
    INTO Employee VALUES ('Abhirup Bag', 'MG Road', 'Mumbai')
    INTO Employee VALUES ('Abhrajit Rath', 'MG Road', 'Mumbai')
    INTO Employee VALUES ('Arpan Kundu', 'Park Street', 'Kolkata')
    INTO Employee VALUES ('ABC', 'Banjara Hills', 'Hyderabad')
    INTO Employee VALUES ('XYZ', 'Ashram Road', 'Ahmedabad')
    INTO Employee VALUES ('Sayan Pal', 'Park Street', 'Kolkata')
select * from dual;

create table company(
    CompanyName varchar2(20) primary key,
    City varchar2(20)
);

insert all
    into company values ('Axis Bank', 'Kolkata')
    into company values ('Google', 'Bangalore')
    into company values ('Amazon', 'Mumbai')
    into company values ('Infosys', 'Hyderabad')
    into company values ('TCS', 'Ahmedabad')
select * from dual;

create table works(
    PersonName varchar2(20) references employee(PersonName) on delete cascade,
    CompanyName varchar2(20) references company(CompanyName) on delete cascade,
    Salary number(8,2)
);

insert all
    into works values ('Abhirup Bag', 'Amazon', '50000')
    into works values ('Abhrajit Rath', 'Google', '45000')
    into works values ('Arpan Kundu', 'Axis Bank', '46000')
    into works values ('ABC', 'Infosys', '31000')
    into works values ('XYZ', 'TCS', '36000')
select * from dual;

create table manages(
    PersonName varchar2(20) references employee(PersonName) on delete cascade,
    ManagerName varchar2(20) references employee(PersonName) on delete cascade
);

insert all
    into manages values ('ABC', 'Abhirup Bag')
    into manages values ('XYZ', 'Abhirup Bag')
    into manages values ('Abhirup Bag', 'Abhrajit Rath')
    into manages values ('Arpan Kundu', 'ABC')
    into manages values ('Abhrajit Rath', 'Sayan Pal')
select * from dual;

-- a)	Find the names of all employees who work for Axis Bank.
select employee.personname 
    from employee join works on employee.personname = works.personname 
    where works.companyname = 'Axis Bank';

-- b)	Find the names and cities of residence of all employees who work for Axis Bank.
select employee.personname, employee.city
    from employee join works on employee.personname = works.personname 
    where works.companyname = 'Axis Bank';

-- c)	Find the names, street addresses, and cities of residence of all employees who work for Axis Bank and earn more than Rs.30000 per annum.
select employee.personname, employee.street, employee.city
    from employee join works on employee.personname = works.personname 
    where works.companyname = 'Axis Bank' and works.salary > 30000;

-- d)	Find all employees who live in the same city as the company for which they work is located.
select employee.* 
    from employee join works on employee.personname = works.personname
    join company on works.companyname = company.companyname
    where employee.city = company.city;

-- e)	Find all employees who live in the same city and on the same street as their managers.
SELECT E.PERSONNAME FROM EMPLOYEE E
WHERE E.CITY IN (SELECT CITY FROM EMPLOYEE WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES))
AND E.STREET IN (SELECT STREET FROM EMPLOYEE WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES))
AND E.PERSONNAME NOT IN (SELECT DISTINCT MANAGERNAME FROM MANAGES);

-- f)	Find all employees in the database who do not work for Axis Bank.
select employee.* from
    employee join works on employee.personname = works.personname 
    where works.companyname != 'Axis Bank';

-- g)	Find all employees who earn more than every employee of Axis Bank. 
select employee.* from 
    employee join works on employee.personname = works.personname 
    where works.salary > (select max(salary) from  
    (select salary from works where companyname='Axis Bank'));

-- or,
select personname from works 
where salary > (select max(salary) from works where companyname='Axis Bank');

-- h)	Assume that the companies may be located in several cities. Find all companies located in every city in which Axis Bank is located.
select distinct companyname 
    from company where city in 
    (select city from company where companyname='Axis Bank') 
    and companyname != 'Axis Bank';

-- i)	Find all employees who earn more than the average salary of all employees of their company.
create table TMPSAL as select companyname, avg(salary) as avgsal from works group by companyname;
select w.* from works w join tmpsal t on w.companyname = t.companyname where w.salary > t.avgsal;

-- j)	Find the company that has the most employees.
create table tmpemps as (select companyname, count(personname) as employees from works group by companyname);
select companyname from tmpemps where (select max(employees) from tmpemps) = employees;

-- k)	Find the company that has the smallest payroll.
create table tmppayroll as 
    (select companyname, sum(salary) as payroll from works group by companyname);
select companyname from tmppayroll 
    where payroll = (select min(payroll) from tmppayroll);

-- l)	Find those companies whose employees earn a higher salary, on average, than the average salary at Axis Bank.
SELECT COMPANYNAME FROM TMPSAL 
    WHERE AVGSAL > (SELECT AVGSAL FROM TMPSAL WHERE COMPANYNAME = 'Axis Bank');

-- m)	Modify the database so that ABC now lives in Kolkata.
update employee set city = 'Kolkata', street = 'Park Street' where personname = 'ABC';

-- n)	Give all employees of Axis Bank a 10 percent raise.
update works set salary = salary + salary * 0.1 where companyname = 'Axis Bank';

-- o)	Give all managers in the database a 10 percent raise.
update works set salary = salary + salary * 0.1 
    where personname in (select distinct managername from manages);

-- p)	Give all managers in the database a 10 percent raise, unless the salary would be greater than Rs.300000. In such cases, give only a 3 percent raise.
UPDATE WORKS SET SALARY = 
    CASE
        WHEN SALARY*1.1 <= 300000 THEN SALARY*1.1
        ELSE SALARY*1.03
    END
    WHERE PERSONNAME IN (SELECT DISTINCT MANAGERNAME FROM MANAGES);

-- q)	Delete all tuples in the works relation for employees of Axis Bank.
delete from employee where personname in
    (select personname from works where companyname = 'Axis Bank');