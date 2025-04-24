create table match (
    match_id varchar2(10) check (match_id like 'M%') primary key,
    team1 varchar2(20) not null,
    team2 varchar2(20) not null,
    ground varchar2(20) not null,
    mdate date not null,
    winner varchar2(20),
    constraint winner_check check (winner = team1 or winner = team2 or winner = 'Draw')
);

insert all
    INTO match VALUES ('M001', 'India', 'Australia', 'Wankhede', TO_DATE ('2024-03-15', 'YYYY-MM-DD'), 'India')
    INTO match VALUES ('M002', 'England', 'Pakistan', 'Lords', TO_DATE ('2024-04-10', 'YYYY-MM-DD'), 'Draw')
    INTO match VALUES ('M003', 'England', 'New Zealand', 'Newlands', TO_DATE ('2024-02-25', 'YYYY-MM-DD'), 'New Zealand')
    INTO match VALUES ('M004', 'Sri Lanka', 'Bangladesh', 'Sri Lanka', TO_DATE ('2024-05-05', 'YYYY-MM-DD'), 'Bangladesh')
    INTO match VALUES ('M005', 'India', 'England', 'Eden Gardens', TO_DATE ('2024-06-12', 'YYYY-MM-DD'), 'England')
    INTO match VALUES ('M006', 'India', 'Australia', 'Sydney', TO_DATE ('2024-03-18', 'YYYY-MM-DD'), 'India')
    INTO match VALUES ('M007', 'India', 'Sri Lanka', 'Sri Lanka', TO_DATE ('2018-04-28', 'YYYY-MM-DD'), 'India')
select * from dual;
select * from match;

create table player(
    p_id varchar2(10) primary key,
    fname varchar2(20) not null,
    lname varchar2(20) not null,
    country varchar2(20) not null,
    yborn number check (yborn < 2009) not null,
    bplace varchar2(20) not null,
    ftest number(2)
);

insert all
    INTO player VALUES ('P001', 'Virat', 'Kohli', 'India', 1988, 'Delhi', 11)
    INTO player VALUES ('27001', 'Steve', 'Smith', 'Australia', 1989, 'Sydney', 10)
    INTO player VALUES ('P003', 'Joe', 'Root', 'England', 1990, 'Sheffield', 12)
    INTO player VALUES ('P004', 'Kane', 'Williamson', 'New Zealand', 1990, 'Tauranga', 10)
    INTO player VALUES ('P005', 'Babar', 'Azam', 'Pakistan', 1994, 'Lahore', 16)
    INTO player VALUES ('P006', 'MS', 'Dhoni', 'India', 1987, 'Ranchi', 20)
    INTO player VALUES ('P007', 'Sakib Ul', 'Hasan', 'Bangladesh', 1995, 'Dhaka', 19)
select * from dual;
select * from player;

create table batting (
    match_id varchar2(10) references match(match_id) on delete cascade,
    p_id varchar2(10) references player (p_id) on delete cascade,
    mts number(2) check (mts >= 0),
    batting_order number(2) check (batting_order > 0 or batting_order < 12),
    out_type varchar2(10) check (out_type in ('b', 'c', 'st', 'lbw', 'run out', 'not out')),
    fow number(2) check (fow > 0),
    nruns number(4) check (nruns >= 0),
    nballs number(3) check (nballs >= 0 and nballs < 300),
    fours number(3) check (fours >= 0 and fours <= 251),
    sixes number(3) check (sixes >= 0 and sixes <= 251)
);

insert all
    INTO batting VALUES ('M001', 'P001', 99, 3, 'b', 2, 75, 95, 8, 1)
    INTO batting VALUES ('M001', '27001', 90, 4, 'c', 3, 105, 90, 6, 5)
    INTO batting VALUES ('M003', 'P003', 96, 2, 'lbw', 1, 88, 102, 10, 0)
    INTO batting VALUES ('M003', 'P004', 85, 5, 'not out', null, 25, 35, 1, 2)
    INTO batting VALUES ('M004', 'P007', 81, 2, 'run out', 6, 98, 123, 3, 5)
    INTO batting VALUES ('M005', 'P005', 77, 1, 'b', 1, 0, 1, 0, 0)
    INTO batting VALUES ('M002', 'P005', 77, 1, 'b', 1, 0, 1, 0, 0)
    INTO batting VALUES ('M006', '27001', 90, 1, 'c', 3, 62, 70, 6, 2)
    INTO batting VALUES ('M001', 'P006', 93, 5, 'c', 5, 153, 100, 10, 9)
    INTO batting VALUES ('M007', 'P006', 93, 5, 'c', 5, 53, 22, 5, 2)
    INTO batting VALUES ('M007', 'P001', 99, 3, 'not out', null, 123, 110, 4, 9)
select * from dual;
select * from batting;

create table bowling(
    match_id varchar2(10) references match(match_id) on delete cascade,
    p_id varchar2(10) references player (p_id) on delete cascade,
    novers number(3, 1) check (novers >= 0 and novers < 10),
    maidens number(2) check (maidens >= 0 and maidens < 10),
    nruns number(3) check (nruns >= 0 and nruns <= 360),
    nwickets number(2) check (nwickets >= 0 and nwickets <= 10)
);

insert all
    INTO bowling VALUES('M001', 'P001', 8.4, 2, 45, 3)
    INTO bowling VALUES('M002', '27001', 9.0, 1, 50, 2)
    INTO bowling VALUES('M003', 'P003', 6.5, 0, 39, 1)
    INTO bowling VALUES('M004', 'P004', 7.2, 1, 60, 4)
    INTO bowling VALUES('M005', 'P005', 5.0, 0, 35, 0)
select * from dual;
select * from bowling;

create table m_test(
    match_id varchar2(10) references match(match_id) on delete cascade,
    primary key(match_id),
    mt_played number(5,1),
    mt_res varchar2(30)
);

insert all
    into m_test values ('M002', 190, 'Draw')
select * from dual;
select * from m_test;

create table m_odi(
    match_id varchar2(10) references match(match_id) on delete cascade,
    primary key(match_id),
    mo_played number(5,1),
    mto_res varchar2(30)
);

insert all
    into m_odi values ('M001', 100, 'India won by 20 runs')
    into m_odi values ('M003', 90.4, 'New Zealand won by 5 runs')
    into m_odi values ('M004', 95.3, 'Bangladesh won by 3 wickets')
    into m_odi values ('M005', 100, 'England won by 1 wickets')
    into m_odi values ('M006', 80.5, 'India won by 150 runs')
    into m_odi values ('M007', 99.2, 'India won by 10 runs')
select * from dual;
select * from m_odi;

-- i) Find match ids of those matches in which player 27001 bats and makes more runs than he made at every match he played at Sydney.
select match_id from batting where nruns > (
    select max(nruns) from (
        select * from batting where match_id in (
            select match_id from match where ground='Sydney'
        ) 
        and p_id = '27001'
    )
) 
and p_id = '27001';

-- ii) Find player ids of players who have scored more than 30 in every ODI match that they have batted.
select distinct p_id from batting where p_id not in (
    select p_id from batting where nruns <= 30 and match_id in (
        select match_id from m_odi
    )
);

--or
-- select p_id from batting where nruns > 30 and p_id not in (
--     select p_id from batting where nruns <= 30
-- ) group by p_id having count(*) = count(nruns); -- no null values

-- iii) Find the ids of players that had a higher average score than the average score for all players when they played in Sri Lanka.
select p_id from (
    select p_id, avg(nruns) as avg_runs from batting group by p_id
) where avg_runs > (
    select avg(nruns) from batting where match_id in (
        select match_id from match where ground = 'Sri Lanka'
    )
);

--Different interpretaion
-- select p_id from (
--     select p_id, avg(nruns) as avg_runs from batting group by p_id
-- ) where avg_runs > (
--     select max(avg_at_wankhede) as max_avg_at_wankhede from (
--         select p_id, avg(nruns) as avg_at_wankhede from batting where match_id in (
--             select match_id from match where ground = 'Sri Lanka'
--         ) group by p_id
--     )
-- );