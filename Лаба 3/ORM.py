from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.sql import func
from sqlalchemy import Column, Integer, String, ForeignKey, Date, Text, Float
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()
metadata = Base.metadata

class Abonent(Base):
    __tablename__ = "Abonent"

    tel = Column(String(10), primary_key=True)
    fio = Column(String(50), nullable=False)

    def __repr__(self):
        return f"<Abonent(tel='{self.tel}', fio='{self.fio}')>"

class Library(Base):
    __tablename__ = 'Library'
    id = Column(Integer, primary_key=True, autoincrement=True)
    address = Column(String(100), nullable=False)
    name = Column(String(25), nullable=False, unique=True)
    time = Column(Integer, nullable=True)

class WorkDays(Base):
    __tablename__ = 'Work_Days'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id = Column(Integer, ForeignKey('library.id', ondelete='CASCADE'))
    day = Column(Integer)

class Vydacha(Base):
    __tablename__ = 'Vydacha'
    id = Column(Integer, primary_key=True, autoincrement=True)
    library = Column(Integer, ForeignKey('library.id', ondelete='CASCADE'))
    chto_vydaetsya = Column(Integer, unique=True, nullable=False)
    tel = Column(String(10), ForeignKey('abonent.tel', ondelete='CASCADE'), nullable=False)
    srok = Column(Integer, nullable=False)

class Organization(Base):
    __tablename__ = 'Organization'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(150), nullable=False, unique=True)
    address = Column(String(100), unique=True)
    web = Column(String(100))

class Journal(Base):
    __tablename__ = 'Journal'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(100), nullable=False, unique=True)
    publisher = Column(Integer, ForeignKey('organization.id', ondelete='CASCADE'))
    start_date = Column(Date, nullable=False)
    end_date = Column(Date)

class LibJour(Base):
    __tablename__ = 'Lib_Jour'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id_lib = Column(Integer, ForeignKey('library.id', ondelete='CASCADE'))
    id_jour = Column(Integer, ForeignKey('journal.id', ondelete='CASCADE'))

class Subgroup(Base):
    __tablename__ = 'Subgroup'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(150), unique=True, nullable=False)
    orgs = Column(Integer, ForeignKey('organization.id', ondelete='CASCADE'))
    specs = Column(String(50))

class Conference(Base):
    __tablename__ = 'Conference'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(100), unique=True, nullable=False)
    city = Column(String(40))
    date = Column(Date, nullable=False)
    descr = Column(Text)
    topic = Column(String(75))

class ConfOrg(Base):
    __tablename__ = 'Conf_Org'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id_org = Column(Integer, ForeignKey('organization.id', ondelete='CASCADE'))
    id_conf = Column(Integer, ForeignKey('conference.id', ondelete='CASCADE'))

class Person(Base):
    __tablename__ = 'Person'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(50))
    mail = Column(String(60), unique=True)
    spec = Column(String(30), nullable=False)
    degree = Column(String(20))

class MemberCommittee(Base):
    __tablename__ = 'Member_Committee'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id_pers = Column(Integer, ForeignKey('person.id', ondelete='CASCADE'))
    id_conf = Column(Integer, ForeignKey('conference.id', ondelete='CASCADE'))
    position = Column(String(30))

class Article(Base):
    __tablename__ = 'Article'
    id = Column(Integer, primary_key=True, autoincrement=True)
    rate = Column(Float, nullable=False)
    date = Column(Date, nullable=False)
    annotation = Column(Text)
    content = Column(Text)
    quotes = Column(Integer, unique=True)
    journal = Column(Integer, ForeignKey('journal.id', ondelete='CASCADE'))

class Quotes(Base):
    __tablename__ = 'Quotes'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id_article = Column(Integer, ForeignKey('article.quotes', ondelete='CASCADE'))
    id_quote = Column(Integer, ForeignKey('article.id', ondelete='CASCADE'))

class Author(Base):
    __tablename__ = 'Author'

    fr_id = Column(Integer, primary_key=True, autoincrement=True)

    id_person = Column(Integer, ForeignKey('person.id', ondelete='CASCADE'))
    id_article = Column(Integer, ForeignKey('article.id', ondelete='CASCADE'))
    id_org = Column(Integer, ForeignKey('subgroup.id', ondelete='CASCADE'))

DATABASE_URL = "sqlite:///SCIENCE_JOURNALS.db"
engine = create_engine(DATABASE_URL, echo=True)
Base = declarative_base()
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

class Queries:
    def __init__(self, engine):
        Session = sessionmaker(bind=engine)
        self.session = Session()

    def get_library_work_days(self):
        return self.session.query(Library.name.label("Библиотека"), WorkDays.day.label("РабочийДень"))\
            .join(WorkDays, Library.id == WorkDays.id)\
            .order_by(Library.name).all()

    def get_past_conferences(self):
        return self.session.query(Conference).filter(Conference.date < func.current_date()).all()

    def get_articles_and_journals(self):
        return self.session.query(Article.annotation.label("Аннотация"), Article.rate.label("Рейтинг"),
                                  Article.date.label("Дата"), Journal.name.label("Журнал"))\
            .join(Journal, Article.journal == Journal.id).all()

    def get_borrowed_journals(self):
        return self.session.query(Abonent.fio, Vydacha.tel, Journal.name, Vydacha.srok)\
            .join(Vydacha, Abonent.tel == Vydacha.tel)\
            .join(Journal, Vydacha.chto_vydaetsya == Journal.id).all()

    def get_moscow_conferences(self):
        return self.session.query(Conference).filter(Conference.city == "Москва").all()

    def get_average_article_rating_per_journal(self):
        return self.session.query(Journal.name.label("Название"), func.avg(Article.rate).label("СреднийРейтинг"))\
            .join(Article, Journal.id == Article.journal)\
            .group_by(Journal.name).all()

    def get_top_author_by_articles(self):
        return self.session.query(Person.name.label("ФИО"), func.count(Author.id_article).label("КолвоСтатей"))\
            .join(Author, Person.id == Author.id_person)\
            .group_by(Person.name)\
            .order_by(func.count(Author.id_article).desc())\
            .limit(1).all()

    def get_library_with_most_issued_journals(self):
        return self.session.query(Library.name.label("Библиотека"), func.count(Vydacha.id).label("Выдано"))\
            .join(Vydacha, Library.id == Vydacha.library)\
            .group_by(Library.name)\
            .order_by(func.count(Vydacha.id).desc())\
            .limit(1).all()

    def get_authors_and_organizations(self):
        return self.session.query(Person.name.label("ФИО"), Organization.name.label("Организация"), Subgroup.name.label("Подразделение"))\
            .join(Author, Person.id == Author.id_person)\
            .join(Subgroup, Author.id_org == Subgroup.id)\
            .join(Organization, Subgroup.orgs == Organization.id).all()

    def get_employee_count_per_organization(self):
        return self.session.query(Organization.name.label("Организация"), func.count(Person.id).label("Персоналий"))\
            .join(Subgroup, Organization.id == Subgroup.orgs)\
            .join(Author, Subgroup.id == Author.id_org)\
            .join(Person, Author.id_person == Person.id)\
            .group_by(Organization.name).all()