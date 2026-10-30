# Fork agent guide

This file adds fork-specific rules on top of the root `AGENTS.md`. When a rule
here conflicts with the root guide, this file wins. Everything not covered here
follows the root guide and `.agents/`.

## Review style

The owner reviews device behavior, not C++ code. Explain each change by what
changes on the device, its costs, and what could break.

## Language

Write everything stored in the repository in English: documents, plans, code
comments, commit messages, and branch names.

## Remotes and branches

- `upstream` is `crosspoint-reader/crosspoint-reader`. Read-only: never push to it.
- `origin` is the fork.
- `develop` mirrors `upstream/develop`. Never commit to it; update it only with
  `git merge --ff-only upstream/develop`.
- `main` is the fork's integration branch. Where the root guide says integration
  work targets `develop`, use `main` instead, including as the review comparison base.
- Feature branches start from `main` and use the root naming rule (`feat/*`, `fix/*`, ...).

## Target devices

| Device | Environment |
| --- | --- |
| Xteink X3 | `default` |
| Xteink X4 Pro | `x4pro` |
| Boox Picco | `picco` |

Each plan names the devices it affects. Build every affected environment; shared
UI code affects all of them. Other boards are not built or tested in this fork.

## Keeping upstream merges easy

Every change must keep the fork's diff against `develop` small:

- Prefer new files over edits to upstream files. Keep edits to upstream files
  to the smallest hunk that works.
- Do not edit `AGENTS.md`, `CLAUDE.md`, `.agents/`, or existing workflows.
  Disable unwanted workflows in the GitHub UI instead.
- Do not delete upstream files.
- Never change `freeink-sdk` or its pinned revision. If a change seems to need
  the SDK, stop and ask the owner.
- Regenerate generated files with their scripts; never hand-edit them or
  hand-resolve their merge conflicts.
- No unrelated cleanup, refactoring, or reformatting.

## Upstream sync

1. `git fetch upstream`, then fast-forward `develop`.
2. Merge `develop` into `main`.
3. `git submodule update --init --recursive`.
4. Resolve conflicts using `docs/fork/PATCHES.md` to recall each change's intent.
5. Build the target environments and report which fork changes need a device recheck.

## Plans and change registry

- Each change has a plan in `docs/fork/plans/NNNN-short-name.md` with the
  requirement, affected devices, acceptance checks on each device, touched
  files, and status.
- `docs/fork/PATCHES.md` lists every fork change: branch or commit, touched
  upstream files, and whether it is an upstream candidate. Update it in the
  same change.
