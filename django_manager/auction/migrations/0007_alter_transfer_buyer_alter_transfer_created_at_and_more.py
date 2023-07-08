# Generated by Django 4.2.2 on 2023-07-08 09:57

import datetime
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('auction', '0006_alter_transfer_created_at'),
    ]

    operations = [
        migrations.AlterField(
            model_name='transfer',
            name='buyer',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='buyer', to='auction.team'),
        ),
        migrations.AlterField(
            model_name='transfer',
            name='created_at',
            field=models.DateTimeField(default=datetime.datetime(2023, 7, 8, 9, 57, 27, 221186, tzinfo=datetime.timezone.utc)),
        ),
        migrations.AlterField(
            model_name='transfer',
            name='seller',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='seller', to='auction.team'),
        ),
    ]
