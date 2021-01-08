import requests
from django.shortcuts import render, redirect
from .models import City
from .forms import CityForm

def index(request):
    url = 'http://api.openweathermap.org/data/2.5/weather?q={}&units=metric&appid=170d7549abb5a495a69167982b41b5c3'

    err_msg = ''
    message = ''
    message_class = ''

    if request.method == 'POST':
        form = CityForm(request.POST)

        if form.is_valid():
            new_city = form.cleaned_data['name']
            existing_city_count = City.objects.filter(name=new_city).count()

            # A check if the new city doesnwt already exist at the list #
            if existing_city_count == 0:
                r = requests.get(url.format(new_city)).json()

                # A check if the new city is valid (404 is not valid) #
                if (r['cod'] == 200):
                    form.save()
                else:
                    err_msg = 'No such city in this world!'
            else:
                err_msg = 'City already exists in the list!'

            if err_msg:
                message = err_msg
                message_class = 'is-danger'
            else:
                message = 'City added successfully'
                message_class = 'is-success'

    form = CityForm()

    cities = City.objects.all()

    weather_data = []

    for city in cities:

        r = requests.get(url.format(city)).json()

        city_weather = {
            'city' :  city.name,
            'temperature' : r['main']['temp'],
            'description' : r['weather'][0]['description'],
            'icon' : r['weather'][0]['icon'],
        }

        weather_data.append(city_weather)

    print()
    print(weather_data)
    print()

    context = {
        'weather_data' : weather_data, 
        'form' : form,
        'message' : message, 
        'message_class' : message_class
    }

    return render(request, 'weather/weather.html', context)

def delete_city(request, city_name):
    City.objects.get(name=city_name).delete()
    return redirect('home')
