import pusher

pusher_client = pusher.Pusher(
  app_id=u'1384821',
  key=u'45da88aa7f5d38d338c4',
  secret=u'aedd886b667484cba54f',
  cluster=u'eu'
)

pusher_client.trigger(u'my-channel', u'dashboard-update', [])