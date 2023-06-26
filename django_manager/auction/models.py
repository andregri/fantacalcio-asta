from django.db import models

# Create your models here.
class Team(models.Model):
    name = models.CharField(max_length=100)
    president = models.CharField(max_length=100)

class Footballer(models.Model):
    GOALKEEPER = "G"
    DEFENDER = "D"
    MIDFIELDER = "C"
    FORWARD = "F"
    ROLE_CHOICES = [
        (GOALKEEPER, "Goalkeeper"),
        (DEFENDER, "Defender"),
        (MIDFIELDER, "Midfielder"),
        (FORWARD, "Forward")
    ]
    name = models.CharField(max_length=200)
    role = models.CharField(max_length=1,
                            choices=ROLE_CHOICES)
    team = models.CharField(max_length=200)
    value = models.PositiveIntegerField()
    fantasy_value = models.PositiveIntegerField()

class Transfer(models.Model):
    created_at = models.DateTimeField()
    footballer = models.ForeignKey(Footballer, on_delete=models.CASCADE)
    seller = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='seller')
    buyer = models.ForeignKey(Team, on_delete=models.CASCADE, related_name='buyer')
