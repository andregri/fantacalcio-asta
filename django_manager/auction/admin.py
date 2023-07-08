from django.contrib import admin
from .models import Team, TeamAdmin, Footballer, FootballerAdmin, Transfer, TransferAdmin

# Register your models here.
admin.site.register(Team, TeamAdmin)
admin.site.register(Footballer, FootballerAdmin)
admin.site.register(Transfer, TransferAdmin)