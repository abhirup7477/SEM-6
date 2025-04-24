create table Cinema(
	cid varchar2(5) check (cid like 'C%') primary key,
	cname varchar2(20) not null,
	city varchar2(20) not null,
	owner_name varchar2(20)
);

create table Film(
	fid varchar2(5) check (fid like 'F%') primary key,
	title varchar2(20) not null,
	director_name varchar2(20) not null,
	genre varchar2(20) not null,
	budget number(7, 2) not null,
	rating number(2,1)
);

create table Showing(
	fid varchar2(10) references Film(fid) on delete cascade,
	cid varchar2(10) references Cinema(cid) on delete cascade,
	primary key (fid, cid)
);

insert all
   into cinema values ('C001', 'ABC', 'Mumbai', 'Ram')
   into cinema values ('C002', 'XYZ', 'Rajkot', 'Shyam')
   into cinema values ('C003', 'MNO', 'Mumbai', 'John')
   into cinema values ('C004', 'BCD', 'Mumbai', 'Joe')
   into cinema values ('C005', 'PQR', 'Rajkot', 'Abir')
select * from dual;

insert all
   into film values ('F001', 'Titanic', 'James', 'Drama', 1, 8.5)
   into film values ('F002', 'Avatar', 'James', 'Sci-Fi', 2, 9.0)
   into film values ('F003', 'Inception', 'Nolan', 'Sci-Fi', 1.5, 8.8)
   into film values ('F004', 'Interstellar', 'Nolan', 'Sci-Fi', 2.5, 9.2)
   into film values ('F005', 'The Dark Knight', 'Nolan', 'Action', 3, 9.5)
   into film values ('F006', 'ABCD', 'XYZ', 'Romance', 3, 9.5)
   into film values ('F007', 'MNOP', 'XYZ', 'Drama', 3, 9.5)
select * from dual;

insert all
	into showing values ('F001', 'C001')
	into showing values ('F006', 'C001')
	into showing values ('F006', 'C002')
	into showing values ('F002', 'C002')
	into showing values ('F005', 'C003')
	into showing values ('F006', 'C003')
	into showing values ('F007', 'C003')
	into showing values ('F007', 'C004')
	into showing values ('F003', 'C005')
select * from dual;