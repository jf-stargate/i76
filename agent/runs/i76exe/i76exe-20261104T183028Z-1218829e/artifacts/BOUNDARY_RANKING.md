# Frozen blind boundary ranking

Scores are ordinal heuristics, not source-file confidence. Feature definitions and counterevidence are in FEATURE_MODEL.md. All adjacent in-range cuts are listed. Context cuts are not ranked.

| Rank | Before entry | Score | State turnover | Call turnover | Caller turnover | Literal turnover | Cross density | Adjacent link | Rank range | Top five / 15 |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 00470660 | 4.5 | 1.0 | 1.0 | 1.0 | 1.0 | 0.0 | 0 | 1–3 | 15 |
| 2 | 00470ca0 | 4.5 | 1.0 | 1.0 | 1.0 | 1.0 | 0.0 | 0 | 1–2 | 15 |
| 3 | 00470cd0 | 4.5 | 1.0 | 1.0 | 1.0 | 1.0 | 0.0 | 0 | 2–3 | 15 |
| 4 | 004703a0 | 4.4 | 1.0 | 0.941 | 1.0 | 0.917 | 0.0 | 0 | 4–5 | 15 |
| 5 | 00470340 | 4.254 | 1.0 | 0.895 | 0.93 | 0.857 | 0.0 | 0 | 4–5 | 15 |
| 6 | 004702d0 | 2.583 | 0.959 | 0.789 | 0.927 | 0.786 | 0.222 | 1 | 6–6 | 0 |
| 7 | 0046fab0 | 2.009 | 0.79 | 0.929 | 1.0 | 1.0 | 0.5 | 1 | 7–10 | 0 |
| 8 | 004704a0 | 1.958 | 0.542 | 0.895 | 1.0 | 0.846 | 0.222 | 1 | 7–16 | 0 |
| 9 | 00470580 | 1.832 | 0.516 | 0.895 | 0.933 | 0.833 | 0.222 | 1 | 9–10 | 0 |
| 10 | 0046ffc0 | 1.698 | 0.782 | 0.765 | 0.31 | 0.786 | 0.667 | 0 | 7–17 | 0 |
| 11 | 00470c70 | 1.696 | 0.577 | 0.833 | 1.0 | 0.75 | 0.333 | 1 | 8–14 | 0 |
| 12 | 00470ac0 | 1.621 | 0.484 | 0.944 | 0.875 | 1.0 | 0.333 | 1 | 11–13 | 0 |
| 13 | 00470070 | 1.551 | 0.782 | 0.778 | 0.927 | 0.786 | 0.556 | 1 | 9–13 | 0 |
| 14 | 00470b20 | 1.479 | 0.715 | 0.882 | 1.0 | 1.0 | 0.667 | 1 | 14–15 | 0 |
| 15 | 00470c40 | 1.06 | 0.672 | 0.8 | 1.0 | 0.5 | 0.667 | 1 | 12–19 | 0 |
| 16 | 0046fd40 | 0.968 | 0.734 | 1.0 | 1.0 | 1.0 | 1.0 | 1 | 12–17 | 0 |
| 17 | 0046fb30 | 0.942 | 0.459 | 0.944 | 0.951 | 0.923 | 0.667 | 1 | 16–18 | 0 |
| 18 | 0046fe30 | 0.613 | 0.769 | 0.769 | 0.326 | 0.625 | 0.667 | 1 | 18–21 | 0 |
| 19 | 00470bc0 | 0.224 | 0.448 | 0.867 | 1.0 | 0.923 | 1.0 | 1 | 15–20 | 0 |
| 20 | 0046fee0 | -0.023 | 0.431 | 0.765 | 0.326 | 0.714 | 0.667 | 1 | 13–21 | 0 |
| 21 | 0046fbe0 | -0.065 | 0.306 | 0.909 | 0.977 | 0.875 | 1.0 | 1 | 18–21 | 0 |

Positive terms quantify feature turnover; cross density and adjacent link are explicit counterevidence. ranking.json retains the exact cross-cut edges and all weighted terms. Zero turnover is also common-ownership evidence. No threshold is a claim of original linkage.

Alternative cuts by score threshold:

- 1.5: 0046fab0, 0046ffc0, 00470070, 004702d0, 00470340, 004703a0, 004704a0, 00470580, 00470660, 00470ac0, 00470c70, 00470ca0, 00470cd0

- 2: 0046fab0, 004702d0, 00470340, 004703a0, 00470660, 00470ca0, 00470cd0

- 2.5: 004702d0, 00470340, 004703a0, 00470660, 00470ca0, 00470cd0
