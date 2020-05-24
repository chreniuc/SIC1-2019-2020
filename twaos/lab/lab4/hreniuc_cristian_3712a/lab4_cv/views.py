from django.shortcuts import render
from django.http import HttpResponse
from django.template import loader
from .models import CV

# Create your views here.
def index(request):
    one_cv = CV.objects.get(cod=0)
    context = {
        'cv': one_cv,
    }

    return render(request, 'lab4_cv/index.html', context)