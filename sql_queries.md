max estimated offer
```
SELECT name, 8 - COALESCE(num_players, 0) AS "toBuy", COALESCE(expense.bought,0) AS "bought", 80 - COALESCE(expense.tot,0) - (8 - COALESCE(num_players, 0)) + 1 AS tot_expense
            FROM team
            LEFT JOIN (
                SELECT roster.fantasy_team_id AS id, COUNT(roster.fantasy_team_id) AS num_players
                FROM roster
                INNER JOIN player ON roster.player_id = player.id
                WHERE player.role = 'D'
                GROUP BY roster.fantasy_team_id) AS count
			ON team.id = count.id
			LEFT JOIN (
				SELECT roster.fantasy_team_id, COALESCE(SUM(transfer.cost), 0) AS tot, COALESCE(COUNT(transfer.cost), 0) AS bought
				FROM roster
				INNER JOIN transfer ON roster.transfer_id = transfer.id
				WHERE roster.player_id IN (
					SELECT id FROM player
					WHERE role = 'D')
				GROUP BY roster.fantasy_team_id
			) AS expense
			ON team.id = expense.fantasy_team_id
			ORDER BY tot_expense DESC
```

Centrocampo
```
SELECT name, 8 - COALESCE(num_players, 0) AS "toBuy", COALESCE(expense.bought,0) AS "bought", 80 - COALESCE(expense.tot,0) - (8 - COALESCE(num_players, 0)) + 1 AS tot_expense
            FROM team
            LEFT JOIN (
                SELECT roster.fantasy_team_id AS id, COUNT(roster.fantasy_team_id) AS num_players
                FROM roster
                INNER JOIN player ON roster.player_id = player.id
                WHERE player.role = 'C'
                GROUP BY roster.fantasy_team_id) AS count
			ON team.id = count.id
			LEFT JOIN (
				SELECT roster.fantasy_team_id, COALESCE(SUM(transfer.cost), 0) AS tot, COALESCE(COUNT(transfer.cost), 0) AS bought
				FROM roster
				INNER JOIN transfer ON roster.transfer_id = transfer.id
				WHERE roster.player_id IN (
					SELECT id FROM player
					WHERE role = 'C')
				GROUP BY roster.fantasy_team_id
			) AS expense
			ON team.id = expense.fantasy_team_id
			ORDER BY tot_expense DESC
```

Attacco
```
SELECT name,
	6 - COALESCE(num_players, 0) AS "toBuy",
	COALESCE(expense.bought,0) AS "bought",
	245 - COALESCE(expense.tot,0) - (6 - COALESCE(num_players, 0)) + 1 AS est_offer,
	COALESCE(500 - team_expense.tot - (25-team_expense.bought) + 1, 500-25+1) AS max_offer
            FROM team
            LEFT JOIN (
                SELECT roster.fantasy_team_id AS id, COUNT(roster.fantasy_team_id) AS num_players
                FROM roster
                INNER JOIN player ON roster.player_id = player.id
                WHERE player.role = 'A'
                GROUP BY roster.fantasy_team_id) AS count
			ON team.id = count.id
			LEFT JOIN (
				SELECT roster.fantasy_team_id, COALESCE(SUM(transfer.cost), 0) AS tot, COALESCE(COUNT(transfer.cost), 0) AS bought
				FROM roster
				INNER JOIN transfer ON roster.transfer_id = transfer.id
				WHERE roster.player_id IN (
					SELECT id FROM player
					WHERE role = 'A')
				GROUP BY roster.fantasy_team_id
			) AS expense
			ON team.id = expense.fantasy_team_id
			LEFT JOIN (
				SELECT roster.fantasy_team_id, COALESCE(SUM(transfer.cost), 0) AS tot, COALESCE(COUNT(transfer.cost), 0) AS bought
				FROM roster
				INNER JOIN transfer ON roster.transfer_id = transfer.id
				GROUP BY roster.fantasy_team_id
			) AS team_expense
			ON team.id = team_expense.fantasy_team_id
			ORDER BY est_offer DESC
```