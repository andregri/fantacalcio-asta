from django.contrib import admin
from .models import Team, Footballer, Transfer

# Register your models here.
admin.site.register(Team)
admin.site.register(Footballer)
admin.site.register(Transfer)