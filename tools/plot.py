import csv
import sys
import matplotlib.pyplot as plt

path = sys.argv[1] if len(sys.argv) > 1 else "sim_log.csv"

t, alt, target, pitch, vs = [], [], [], [], []
with open(path) as f:
    for row in csv.DictReader(f):
        t.append(float(row["time_s"]))
        alt.append(float(row["altitude_m"]))
        target.append(float(row["target_m"]))
        pitch.append(float(row["pitch_cmd_deg"]))
        vs.append(float(row["vertical_speed_mps"]))

fig, axes = plt.subplots(3, 1, sharex=True, figsize=(9, 8))

axes[0].plot(t, alt, label="altitude")
axes[0].plot(t, target, "--", label="target")
axes[0].set_ylabel("Altitude (m)")
axes[0].legend()

axes[1].plot(t, pitch, color="tab:orange")
axes[1].set_ylabel("Pitch cmd (deg)")

axes[2].plot(t, vs, color="tab:green")
axes[2].set_ylabel("Vertical speed (m/s)")
axes[2].set_xlabel("Time (s)")

for ax in axes:
    ax.grid(True, alpha=0.3)

fig.tight_layout()
fig.savefig("sim_plot.png", dpi=150)
plt.show()