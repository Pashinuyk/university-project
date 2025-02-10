--ПО КАКИМ ДНЯМ РАБОТУЮТ БИБЛИОТЕКИ
SELECT Name AS Библиотека, Day As РабочийДень FROM Library INNER JOIN Work_Days ON Library.ID = Work_Days.ID ORDER BY Name;

--КОНФЕРЕНЦИИ КОТОРЫЕ УЖЕ ПРОШЛИ
SELECT * FROM Conference WHERE Date < DATE('now');

--СТАТЬИ И ИХ ЖУРНАЛЫ
SELECT Article.Annotation AS Аннотация, Article.Rate AS Рейтинг, Article.Date AS Дата, Journal.Name AS Журнал  
FROM Article  
JOIN Journal ON Article.Journal = Journal.ID;

--КТО ЧТО ВЗЯЛ ИЗ БИБЛИОТЕКИ
Select FIO, Vydacha.tel, Name, srok FROM Vydacha INNER JOIN Abonent ON Abonent.tel = Vydacha.tel
INNER JOIN Journal ON Vydacha.CHTO_VYDAETSYA = Journal.ID;

--КОНФЕРЕНЦИИ, ПРОШЕДШИЕ В МОСКВЕ
SELECT * FROM Conference WHERE City = 'Москва';

--СРЕДНИЙ РЕЙТИНГ ВСЕХ СТАТЕЙ КАЖДОГО ЖУРНАЛА
SELECT Name AS Название, AVG(Article.Rate) AS СреднийРейтинг  
FROM Journal  
JOIN Article ON Journal.ID = Article.Journal  
GROUP BY Journal.Name;

--АВТОР С НАИБОЛЬШИМ ЧИСЛОМ СТАТЕЙ
SELECT Person.Name AS ФИО, COUNT(Author.ID_Article) AS КолвоСтатей 
FROM Person  
JOIN Author ON Person.ID = Author.ID_Person  
GROUP BY Person.Name  
ORDER BY КолвоСтатей DESC  
LIMIT 1;

--БИБЛИОТЕКА, ГДЕ ВЫДАЛИ БОЛЬШЕ ВСЕГО ЖУРНАЛОВ
SELECT Name AS Библиотека, COUNT(Vydacha.ID) AS Выдано  
FROM Library  
JOIN Vydacha ON Library.ID = Vydacha.Library  
GROUP BY Library.Name  
ORDER BY Выдано DESC  
LIMIT 1;

--АВТОРЫ И ИХ ОРГАНИЗАЦИЯ
SELECT Person.Name AS ФИО, Organization.Name AS Организация, Subgroup.Name AS Подразделение
FROM Author  
JOIN Person ON Author.ID_Person = Person.ID  
JOIN Subgroup ON Author.ID_Org = Subgroup.ID  
JOIN Organization ON Subgroup.Orgs = Organization.ID;

--ЧИСЛО СОТРУДНИКОВ КАЖДОЙ ОРГАНИЗАЦИИ
SELECT Organization.Name AS Организация, COUNT(Person.ID) AS Персоналий 
FROM Person  
JOIN Author ON Person.ID = Author.ID_Person  
JOIN Subgroup ON Author.ID_Org = Subgroup.ID  
JOIN Organization ON Subgroup.Orgs = Organization.ID  
GROUP BY Organization.Name;