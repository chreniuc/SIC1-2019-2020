from django.db import models

# Create your models here.


class Experience(models.Model):
    title = models.CharField(max_length=100)
    company = models.CharField(max_length=100)
    start_date = models.DateField()
    end_date = models.DateField(null=True)
    location = models.CharField(max_length=100)
    description = models.CharField(max_length=1024)

class Education(models.Model):
    title = models.CharField(max_length=100)
    name = models.CharField(max_length=100)
    start_date = models.DateField()
    end_date = models.DateField(null=True)
    location = models.CharField(max_length=100)
    description = models.CharField(max_length=1024)

class Skills(models.Model):
    title = models.CharField(max_length=100)
    endorsements = models.IntegerField(default=0)

class Courses(models.Model):
    title = models.CharField(max_length=100)

class Languages(models.Model):
    title = models.CharField(max_length=100)
    level = models.CharField(max_length=10)

class Honors_n_Awards(models.Model):
    title = models.CharField(max_length=100)
    award = models.CharField(max_length=100)

class Accomplishments(models.Model):
    courses = models.ManyToManyField(Courses)
    languages = models.ManyToManyField(Languages)
    honors_n_awards = models.ManyToManyField(Honors_n_Awards)

class Interests(models.Model):
    title = models.CharField(max_length=100)
    followers = models.IntegerField(default=0)


class CV(models.Model):
    cod = models.IntegerField(default=0)
    first_name = models.CharField(max_length=64)
    middle_name = models.CharField(max_length=64)
    last_name = models.CharField(max_length=64)
    picture_link = models.CharField(max_length=100)
    birthday = models.DateField()
    current_job = models.CharField(max_length=100)
    location = models.CharField(max_length=200)
    experience = models.ManyToManyField(Experience)
    education = models.ManyToManyField(Education)
    skills = models.ManyToManyField(Skills)
    accomplishments = models.ManyToManyField(Accomplishments)
    interests = models.ManyToManyField(Interests)