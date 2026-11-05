"""Analytical source-selection model of 004B2E00, not retail execution.

A plan describes handle closure/media-callback side effects before acquisition.
No filesystem, archive provider, cache, or maintained reconstruction integration.
"""
from dataclasses import dataclass

@dataclass(frozen=True)
class Source:
    mode: int
    media: int = 0

@dataclass(frozen=True)
class Selection:
    ordinal: int
    close_all_archives: bool = False
    switch_media: int | None = None


def select(sources, membership: int, media_enabled: bool, active_media: int):
    if len(sources)>256 or membership<0 or membership>>len(sources):
        raise ValueError('invalid source membership')
    members=[i for i in range(len(sources)) if membership & (1<<i)]
    if not members: raise KeyError('no member source')
    first=members[0]
    media=[i for i in members if sources[i].mode==0]
    if not media_enabled or not media or first<media[0]:return Selection(first)
    active=[i for i in media if sources[i].media==active_media]
    if active:return Selection(active[0])
    return Selection(media[0],True,sources[media[0]].media)
