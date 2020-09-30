#pragma once

#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class Song : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString uniqueId READ uniqueId CONSTANT)
        Q_PROPERTY(QString title READ title CONSTANT)
        Q_PROPERTY(QString artist READ artist CONSTANT)
        Q_PROPERTY(QString album READ album CONSTANT)
        Q_PROPERTY(QString artUrl READ artUrl CONSTANT)
        Q_PROPERTY(double duration READ duration NOTIFY durationChanged)
        Q_PROPERTY(bool isFavorite READ isFavorite NOTIFY isFavoriteChanged)
    public:
        Song();
        Song(const QString& uniqueId,
             const QString& title,
             const QString& artist,
             const QString& album,
             const QString& artUrl,
             double duration,
             bool isFavorite);

        QString uniqueId() const;
        QString title() const;
        QString artist() const;
        QString album() const;
        QString artUrl() const;
        double duration() const;
        bool isFavorite() const;

        void setDuration(double value);
        void setFavorite(bool value);
        void setArtUrl(const QString& artUrl);

        bool operator==(const Song& other) const
        {
            return _uniqueId == other._uniqueId;
        }
        bool operator!=(const Song& other) const
        {
            return !this->operator==(other);
        }

        Q_INVOKABLE bool isValid() const
        {
            return !_uniqueId.isEmpty() && !toString().isEmpty();
        }

        QString toString() const
        {
            if (!_artist.isEmpty())
                return _title + " by " + _artist;
            else
                return _title;
        }

        std::shared_ptr<Song> clone() const
        {
            return std::make_shared<Song>(uniqueId(), title(), artist(), album(), artUrl(), duration(), isFavorite());
        }

    signals:
        void durationChanged();
        void isFavoriteChanged();
        void artUrlChanged();

    private:
        QString _uniqueId;
        QString _title;
        QString _artist;
        QString _album;
        QString _artUrl;
        double _duration;  // in seconds
        bool _isFavorite;
    };
}
