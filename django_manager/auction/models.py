from django.db import models
from django.utils import timezone

# Create your models here.
class Team(models.Model):
    name = models.CharField(max_length=100)
    president = models.CharField(max_length=100)

    def __str__(self):
        return self.name

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
    name = models.CharField(max_length=200)
    role = models.CharField(max_length=1,
                            choices=ROLE_CHOICES)
    team = models.CharField(max_length=200)
    value = models.PositiveIntegerField()
    fantasy_value = models.PositiveIntegerField()

    def __str__(self):
        return f"[{self.role}] {self.name} ({self.team})"

class Transfer(models.Model):
    created_at = models.DateTimeField(default=timezone.now())
    footballer = models.ForeignKey(Footballer, on_delete=models.CASCADE)
    seller = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='seller', null=True, blank=True)
    buyer = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='buyer', null=True, blank=True)
    cost = models.PositiveIntegerField()

    def __str__(self):
        return f"{self.cost}€ {self.footballer} -> {self.buyer}"
