from django.contrib import admin
from .models import CV,Experience ,Education , Skills, Courses , Languages, Honors_n_Awards, Accomplishments, Interests
# Register your models here.

admin.site.register(CV)
admin.site.register(Experience)
admin.site.register(Education)
admin.site.register(Skills)
admin.site.register(Courses)
admin.site.register(Languages)
admin.site.register(Honors_n_Awards)
admin.site.register(Accomplishments)
admin.site.register(Interests)