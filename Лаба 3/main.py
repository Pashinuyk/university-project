from fastapi import FastAPI, Depends
from sqlalchemy.orm import Session
from sqlalchemy import create_engine
from ORM import Queries, SessionLocal, engine, Base
engine = create_engine("sqlite:///SCIENCE_JOURNALS.db")
zapr = Queries(engine)

Base.metadata.create_all(bind=engine)

app = FastAPI(title="Library REST API")

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

#ПО КАКИМ ДНЯМ РАБОТАЮТ БИБЛИОТЕКИ
@app.get("/libraries/work-days")
def library_work_days(db: Session = Depends(get_db)):
    result = zapr.get_library_work_days()
    return {"Результат:": [{"Библиотека": row.Библиотека, "РабочийДень": row.РабочийДень} for row in result]}

#КОНФЕРЕНЦИИ, КОТОРЫЕ УЖЕ ПРОШЛИ
@app.get("/conferences/past")
def conference_past(db: Session = Depends(get_db)):
    result = zapr.get_past_conferences()
    return {"Результат:": [{"Name": row.name, "City": row.city, "Date": row.date, "Descr": row.descr, "Topic": row.topic} for row in result]}

#СТАТЬИ И ИХ ЖУРНАЛЫ
@app.get("/articles/journals")
def article_and_journal(db: Session = Depends(get_db)):
    result = zapr.get_articles_and_journals()
    return {"Результат:": [{"Аннотация": row.Аннотация, "Рейтинг": row.Рейтинг, "Дата": row.Дата, "Журнал": row.Журнал} for row in result]}

#КТО ЧТО ВЗЯЛ ИЗ БИБЛИОТЕКИ
@app.get("/journals/borrowed")
def borrowed_journals(db: Session = Depends(get_db)):
    result = zapr.get_borrowed_journals()
    return {"Результат:": [{"FIO": row.fio, "tel": row.tel, "Name": row.name, "Srok": row.srok} for row in result]}

#КОНФЕРЕНЦИИ, ПРОШЕДШИЕ В МОСКВЕ
@app.get("/conferences/moscow")
def moscow_conferences(db: Session = Depends(get_db)):
    result = zapr.get_moscow_conferences()
    return {"Результат:": [{"ID": row.id, "Name": row.name, "City": row.city, "Date": row.date, "Descr": row.descr, "Topic": row.topic} for row in result]}

#СРЕДНИЙ РЕЙТИНГ ВСЕХ СТАТЕЙ КАЖДОГО ЖУРНАЛА
@app.get("/journals/rate")
def average_rating(db: Session = Depends(get_db)):
    result = zapr.get_average_article_rating_per_journal()
    return {"Результат:": [{"Название": row.Название, "Средний рейтинг": row.СреднийРейтинг} for row in result]}

#АВТОР С НАИБОЛЬШИМ ЧИСЛОМ СТАТЕЙ
@app.get("/authors/top")
def top_author(db: Session = Depends(get_db)):
    result = zapr.get_top_author_by_articles()
    return {"Результат:": [{"ФИО": row.ФИО, "Количество статей": row.КолвоСтатей} for row in result]}

#БИБЛИОТЕКА, ГДЕ ВЫДАЛИ БОЛЬШЕ ВСЕГО ЖУРНАЛОВ
@app.get("/libraries/issued_journals")
def issued_journals(db: Session = Depends(get_db)):
    result = zapr.get_library_with_most_issued_journals()
    return {"Результат:": [{"Библиотека": row.Библиотека, "Выдано": row.Выдано} for row in result]}

#АВТОРЫ И ИХ ОРГАНИЗАЦИЯ
@app.get("/authors/organization")
def authors_organization(db: Session = Depends(get_db)):
    result = zapr.get_authors_and_organizations()
    return {"Результат:": [{"ФИО": row.ФИО, "Организация": row.Организация, "Подразделение": row.Подразделение } for row in result]}

#ЧИСЛО СОТРУДНИКОВ КАЖДОЙ ОРГАНИЗАЦИИ
@app.get("/organizations/persons")
def employee_count(db: Session = Depends(get_db)):
    result = zapr.get_employee_count_per_organization()
    return {"Результат:": [{"Организаций": row.Организация, "Персоналий": row.Персоналий} for row in result]}



if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
