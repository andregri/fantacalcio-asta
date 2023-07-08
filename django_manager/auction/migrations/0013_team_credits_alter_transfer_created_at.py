# Generated by Django 4.2.2 on 2023-07-08 10:16

import datetime
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auction', '0012_alter_transfer_created_at'),
    ]

    operations = [
        migrations.AddField(
            model_name='team',
            name='credits',
            field=models.PositiveIntegerField(default=500),
            preserve_default=False,
        ),
        migrations.AlterField(
            model_name='transfer',
            name='created_at',
            field=models.DateTimeField(default=datetime.datetime(2023, 7, 8, 10, 16, 22, 826543, tzinfo=datetime.timezone.utc)),
        ),
    ]
