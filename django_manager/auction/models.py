from django.db import models
from django.utils import timezone
from django.contrib import admin

class TeamAdmin(admin.ModelAdmin):
    list_display = ["name"]

class Team(models.Model):
    name = models.CharField(max_length=100)
    president = models.CharField(max_length=100)

    def __str__(self):
        return self.name

class FootballerAdmin(admin.ModelAdmin):
    list_display = ["name", "role", "team", "fantasy_value"]
    search_fields = ["name", "team"]

class Footballer(models.Model):
    GOALKEEPER = "P"
    DEFENDER = "D"
    MIDFIELDER = "C"
    FORWARD = "A"
    ROLE_CHOICES = [
        (GOALKEEPER, "Portiere"),
        (DEFENDER, "Difensore"),
        (MIDFIELDER, "Centrocampista"),
        (FORWARD, "Attaccante")
    ]
    external_id = models.CharField(max_length=200)
    name = models.CharField(max_length=200)
    role = models.CharField(max_length=1,
                            choices=ROLE_CHOICES)
    team = models.CharField(max_length=200)
    value = models.PositiveIntegerField()
    fantasy_value = models.PositiveIntegerField()

    def __str__(self):
        return f"{self.name} ({self.team})"

class TransferAdmin(admin.ModelAdmin):
    list_display = ["get_role", "footballer", "buyer", "cost"]
    list_filter = ["buyer", "footballer__role"]
    ordering = ['-created_at']
    autocomplete_fields = ['footballer']

    @admin.display(
        description='role',
    )
    def get_role(self, obj):
        return obj.footballer.role

class Transfer(models.Model):
    created_at = models.DateTimeField(default=timezone.now())
    footballer = models.ForeignKey(Footballer, on_delete=models.CASCADE)
    seller = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='seller', null=True, blank=True)
    buyer = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='buyer', null=True, blank=True)
    cost = models.PositiveIntegerField()

    def __str__(self):
        return f"{self.cost}€ {self.footballer} -> {self.buyer}"
